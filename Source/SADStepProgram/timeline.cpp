#include "timeline.h"
#include <QTimer>
#include <QList>
#include "GameCanvas.h"
#include <QtDebug>
#include <cmath>
#include <QPair>

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
//TODO Stop functionality, Hold functionality, Mine functionality
Timeline::Timeline(QList<QPair<double,double>* >* BPM, QList<QList<QList<int>*>*>* arrowData
		   ,double songLength, double distance, double speed) {
    qDebug() << "hello";/*
    dt = 0; // used as a counter in deletion proccess (see checkTime function)
    ct = 0; // used as a counter in creation proccess (see createTime function)*/
    double totalTime = 0;
    double lastDeconTime = 0;
    double errorsize = 0;
    double beatCounter = 0.0;
    double measureBPM = 0.0;

    creationTime = new QList<double>;
    destructionTime = new QList<double>;
    // double sLength = songLength;
/*
    bool useX = false;
    if (arrowData->size() == BPM->size()) {
	useX = true;
    } else if(BPM->size()==1) {
	useX = false;
    } else {
	//If BPM size and Arrow size don't match, AND BPM size isn't equall to
	//one, THEN and only then did an error occur.
	//  TODO Throw Error
    }
*/
    for(int x=0;x < arrowData->size();x++){
	//Eg:
	//0 0 0 1
	//1 0 0 2
	//0 0 1 0
	//0 0 0 3
	//Does not ignore zero vectors since they are still counted in the game
        QList<QList<int>* >* measureData = arrowData->at(x);
        for(int w = 0; w < measureData->size(); w++)
        {
            measureBPM = BPM->at(0)->second;//loads in the initial BPM
            double measureSize = measureData->size();
            double divisionFactor = measureSize/4; /*for 8/4 time we'd get 2, 4/4 would be 1, so we have
                                                     the factor of division*/
            beatCounter += 1/divisionFactor; //this keeps track of how many beats have occured. it divides
                                             //each note into a beat, so we will have

            qDebug() << beatCounter << "is the beat";

            for(int y = 1; y < BPM->size(); y++)//this is ignored if there is only one BPM
            {
                QPair<double,double>* bpmInfo = BPM->at(y);
                if (beatCounter > bpmInfo->first)//used if multiple BPMs exist
                {
                    measureBPM = BPM->at(y+1)->second; //this reads in the next bpm. It then increments y,
                                                       //the exits the loop
                }
                else
                {break;}//used most of the time. happens when beatCounter isn't at the BPM change yet.
            }

            /*
              need to do: create a vector of times when the bpm changes for gamecanvas
                          need to calculate each time the BPM changes the times of each
                             of the 6 notes after it, so their decon and constr. times
                             can be calculate
                          need to add in old code that reads indiv. notes to it can
                             decide if it is a hold note or not
            */
            qDebug() << measureBPM << "bpm";
	    //Find the speed of a quarter note
	    measureBPM/=60; //Beats per second
	    measureBPM=1/measureBPM; //Seconds per beat
	    measureBPM*=1000; //milliseconds per beat

	    qDebug() << measureBPM << "Milliseconds per beat";
	    //We now have our time for a quarter note. Next, find the number of
	    //notes in a particular measure and calculate the proper division
            //factor

	    double noteTime = measureBPM/divisionFactor;

	    //Now we have the time at which the note ought to deconstruct.
	    //We need to find the time at which it constructs.
	    //In theory this should be the deconstruction Time, minus whatever
	    //time it took the arrow to get accross screen. To caculate this, we
	    //need to know:
	    //The distance of the screen (not arbitrary)
	    //The speed (arbitrary) at which it is traveling
	    //creationTime = deconstructionTime - distance/speed

            //may need to add if-then statement here to account for 0000's so
            //game isnt creating times for nothing

	    double deconTime = noteTime+totalTime;
	    qDebug() << deconTime << " decon";
	    this->destructionTime->append(deconTime);
	    totalTime+=noteTime; //Add in note to totalTime

            double arrowSpeed = distance*(1/noteTime);

            this->creationTime->append((deconTime-lastDeconTime)-(distance/arrowSpeed));
	    qDebug() << ((deconTime-lastDeconTime)-(distance/speed)) << " create";
	    lastDeconTime = deconTime;
            errorsize+=creationTime->last()-std::floor(creationTime->last());
	}
    }
    qDebug() << "error time" << errorsize;
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
void Timeline::calculateTimes (int speed, int distance)
{
    arrowSpeed = (distance/speed);
    timelineDistance = distance;
}
