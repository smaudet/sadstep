#include "timeline.h"
#include <QTimer>
#include <QList>
#include "GameCanvas.h"
#include <QtDebug>

Timeline::Timeline()
{
// shouldn't happen
}
/*
  Sebastian Audet

  AFAIK - Dance files look in general like this:

  (example)
  104J99
  001102
  ,
  002210
  000000
  003010
  ,
  8800II
  832901
  000000
  011001

  So we have a Vector of ints, i.e. 011010
  inside a vector of those i.e.
  011010
  *(something similar here)
  *(ditto)

  And a Vector of those i.e.

  *(What we had above)
  ,
  *(Another similar one
  ,
  *(etc, you get the idea

  So we have a Vector of a Vector of a Vector of values, namely ints.

  Then our custom BPM looks like so:
  10,
  20,
  40,
  30,

  etc. i.e. a Vector of values

  The only thing that could be out there that I may have forgotten about
  is tracks with individual bpm tracks, i.e. instead of rows of notes with beats,
  we have rows of bpm times....however I think we discussed not doing that. But in that case
  you would only have one vector, a Vector of a Vector of values.

  */
Timeline::Timeline(QList<double>* BPM, QList<QList<QList<int>*>*>* arrowData, double songLength)
{
    qDebug() << "hello";
    dt = 0; // used as a counter in deletion proccess (see checkTime function)
    ct = 0; // used as a counter in creation proccess (see createTime function)
    int loadInCon = 0; //final product of math for creation time.
    int loadInDecon = 0; //same as above, but destruction.
    double indivBPM, indivBPmS = 0;
    int noteDeconTime = 0;
    double buffer = 0;

    creationTime = new QList<int>;
    destructionTime = new QList<int>;
    // double sLength = songLength;

    if (arrowData->size() == BPM->size())
    {
        for (int x=0; x < arrowData->size(); x++)
        {
            QList<QList<int>*>* measureData = arrowData->at(x);
            for(int w = 0; w < measureData->size(); w++)
            {
                if (measureData->at(w)!= 0000)
                {
                    // REMINDER::Arrow Creator class takes care of dealing with
                    //(0000) vectors. This class ignors them.
                    indivBPM = BPM->at(x)/measureData->size();
                    indivBPmS = indivBPM/60000; //converts BPM to Beats per millisecond
                    noteDeconTime = 1/indivBPmS; //gets milliseconds per beat(ie note)
                    if (destructionTime->isEmpty())
                    {
                        loadInDecon = noteDeconTime; //used to load in initial value for destructionTime
                    }
                    else
                    {
                        loadInDecon = destructionTime->last() + noteDeconTime;
                    }   //above eqn. compounds the time in dT
                    destructionTime->append(loadInDecon);
                    loadInCon = destructionTime->last() - 5000; //Assuming it takes 5 seconds for arrows to
                    creationTime->append(loadInCon);            //travle across the screen.
                    qDebug() << "creation time size" << creationTime->size();
                }
                else
                {
                    //TODO What is this else statement for? - Sebastian
                }
            }
        }
    }
    else if(BPM->size()==1) {
        for (int x=0; x < arrowData->size(); x++)
        {
            QList<QList<int>*>* measureData = arrowData->at(x);
            for(int w = 0; w < measureData->size(); w++)
            {
                    // REMINDER::Arrow Creator class takes care of dealing with
                    //(0000) vectors. This class ignors them.
                    double measureBPS = BPM->at(0);
                    measureBPS*=1000;
                    //indivBPmS = indivBPM/60; //converts BPM to Beats per second
                    qDebug() << measureBPS << "bps" << measureBPS/measureData->size();
                    noteDeconTime = measureBPS/measureData->size();
                    //noteDeconTime = 1/indivBPmS*1000; //gets milliseconds per beat(ie note)
                    qDebug() << noteDeconTime;
                    destructionTime->append(noteDeconTime+loadInDecon);
                    loadInDecon = destructionTime->last();
                    loadInCon = loadInDecon; //Assuming it takes 5 seconds for arrows to
                    creationTime->append(loadInCon);            //travle across the screen.
                    qDebug() << "creation time" << loadInCon;

            }
        }
    } else {
        //If BPM size and Arrow size don't match, AND BPM size isn't equall to
        //one, THEN and only then did an error occur.
    }
}

void Timeline::getNotes(QList<QList<QList<int>*>*>* arrowData) {
    //This function takes arrowData, which is grouped in Measures, which are
    //a bunch of lines with "arrows" in them, and puts them into one large
    //measure.
    //(example)
    //0010
    //0100  (each block is a measure. each line represents the arrows.)
    //1000
    //,
    //0001
    //1010
    //0101
    //,
    //will now read
    //0010
    //0100
    //1000
    //0001
    //1010
    //0101
    QList<QList<int>*>* localMeasure;
    
    arrowGiantMeasure = new QList<QList<int>*>;
    for (int x = 0; x < arrowData->size(); x++)
    {
        localMeasure = arrowData->at(x);
        arrowGiantMeasure->append(*localMeasure);
    }
    qDebug() << "arrowGiantMeasure" << arrowGiantMeasure->size();
}

int Timeline::getArrowSpeed()
{
    arrowSpeed = (distance/5000); // may change to include BPM @ later date
    return arrowSpeed;
}

void Timeline::setDistance(int distance) {
    this->distance = distance;
}

int Timeline::timeDisplacement(int pushTimer) // used to send time to Score class
{
    //int getPushTime(pushTimer); not needed atm
    //scorePushTime = checkTime();
    // helps give time in absolute value for distance
    //between when arrow should have been pushed and is pushed
    if (pushTimer > scorePushTime)
     {
    displacement = (pushTimer - scorePushTime);
    }
    else
     {
        displacement = (scorePushTime - pushTimer);
    }

    return displacement;
}

int Timeline::createTime() //returns creation time for arrows 1 set at a time
{
    cTime = creationTime->at(ct);
    return cTime;
    ++ct;
}
int Timeline::checkTime() // returns time for destruction 1 arrow set at a time
{
    dTime = destructionTime->at(dt);
    return dTime;
    ++dt;
}
Timeline::~Timeline() // destructor
{

}
