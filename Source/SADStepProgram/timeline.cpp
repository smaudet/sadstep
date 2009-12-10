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
    double indivBPM, indivBPmS, noteBPM = 0;
    double noteTime, restTime = 0;
    double noteDeconTime = 0;

    creationTime = new QList<int>;
    destructionTime = new QList<int>;
    // double sLength = songLength;

    if ((arrowData->size() == BPM->size()) || (BPM->size() == 1))
    {   //makes sure that BPM has either one bpm, or a bpm for each measure.
        for (int x=0; x < arrowData->size(); ++x) //loop used to read in the first internal QList
        {
            QList<QList<int>*>* measureData = arrowData->at(x);
            for(int w = 0; w < measureData->size(); ++w) //loop used to read the second internal QList
            {
                QList<int>* noteData = measureData->at(w);
                bool notePresent;
                for(int y = 0; y < noteData->size(); ++y)//loop checks for the presence of notes
                {

                    if (noteData->at(y) != 0)
                    {
                        notePresent = true;
                        break;
                    }
                    else
                    {
                        notePresent = false;
                    }

                }

                if (notePresent) //If a note is present, the time the note gets is calculated and a
                {                //deconstructionTime and creationTime is added to respective QLists.
                    // REMINDER::Arrow Creator class takes care of dealing with
                    //(0000) vectors. This class ignors them.
                    noteBPM = measureData->size()/4.0;
                    qDebug() << "our bpm reads in as" << BPM->at(0);
                    if (BPM->size()==1) //if there is only one bpm.
                    {indivBPM = BPM->at(0)/noteBPM;}
                    else                //if there are bpm's for each measure.
                    {indivBPM = BPM->at(x)/noteBPM;}
                    qDebug() << "Our BPM is" << indivBPM;
                    indivBPmS = indivBPM/60000; //converts BPM to Beats per millisecond
                    noteDeconTime = 1/indivBPmS; //gets milliseconds per beat(ie note)
                    if (destructionTime->isEmpty())
                    {
                        loadInDecon = noteDeconTime + restTime;
                    }   //used to load in initial value for destructionTime
                    else
                    {
                        loadInDecon = destructionTime->last() + noteDeconTime + restTime;
                    }   //above eqn. compounds the time in dT
                    destructionTime->append(loadInDecon);
                    qDebug() << "load in time" << loadInDecon;
                    loadInCon = destructionTime->last(); //Assuming it takes 5 seconds for arrows to
                    creationTime->append(loadInCon);            //travle across the screen.
                    qDebug() << "creation time size" << creationTime->size();
                    restTime = 0;
                }
                /*else//If the note contains all zeros, only the time is calculated.
                    //It is then added to itself until a note with arrows is found.
                {   //This ensure that rests are taken into account.
                    noteBPM = measureData->size()/4.0;
                    if (BPM->size()==1) //if there is only one bpm.
                    {indivBPM = BPM->at(0)/noteBPM;}
                    else                //if there are bpm's for each measure.
                    {indivBPM = BPM->at(x)/noteBPM;}
                    indivBPmS = indivBPM/60000; //converts BPM to Beats per millisecond
                    noteTime = 1/indivBPmS; //gets milliseconds per beat(ie note)
                    restTime = restTime + noteTime;
                    qDebug() << "rest measure";
                }*/
                qDebug() << "adds 1 to w";
            }
            qDebug() << "adds 1 to x";
        }
    }
   /* else if(BPM->size()==1) {
        for (int x=0; x < arrowData->size(); x++)
        {
            double measureBPS;
            QList<QList<int>*>* measureData = arrowData->at(x);
            for(int w = 0; w < measureData->size(); w++)
            {
                    // REMINDER::Arrow Creator class takes care of dealing with
                    //(0000) vectors. This class ignors them.
                    measureBPS = BPM->at(0)/60;
                    measureBPS*=1000;
                    qDebug() << measureBPS << "bps" << measureBPS/measureData->size();
                    noteDeconTime = measureBPS/measureData->size();
                    qDebug() << noteDeconTime;
                    destructionTime->append(noteDeconTime+loadInDecon);
                    loadInDecon = destructionTime->last();
                    loadInCon = loadInDecon; //Assuming it takes 5 seconds for arrows to
                    creationTime->append(loadInCon);            //travle across the screen.
                    qDebug() << "creation time" << loadInCon;

            }
        }
    }*/
    else {
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

/*int Timeline::timeDisplacement(int pushTimer) (old code. new code implemented in mainwindow.cc)
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
}*/

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
