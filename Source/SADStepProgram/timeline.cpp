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
    double note_mSPB = 0.0; //note's milliseconds per beat
    qDebug() << "how are you?";
    creationTime = new QList<double>;
    destructionTime = new QList<double>;
    holdCounters = new QList<QList<double>*>;
    QList<double>* noteHoldTime = new QList<double>;

    // double sLength = songLength;
    qDebug() << "really?";
    for(int u=0; u<4; u++) //Initializes holdCounters to have 4 different QLists for each lane
    {
        QList<double>* temp = new QList<double>;
        holdCounters->append(temp);
    }
    qDebug() << "that is good.";
    measureBPM = BPM->at(0)->second;//loads in the initial BPM
    qDebug() << measureBPM << " well, shall we begin?";
    for(int x=0;x < arrowData->size();x++){
        qDebug() << "Phase one complete";
	//Eg:
	//0 0 0 1
	//1 0 0 2
	//0 0 1 0
	//0 0 0 3
	//Does not ignore zero vectors since they are still counted in the game

        QList<QList<int>* >* measureData = arrowData->at(x);
        for(int w = 0; w < measureData->size(); w++)
        {
            qDebug() << "Phase two complete";
            double measureSize = measureData->size();
            qDebug()<< measureSize << " is measure size";
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
                    bpmChanges->append(lastDeconTime);
                }
                else
                {break;}//used most of the time. happens when beatCounter isn't at the BPM change yet.
            }
            /*
              need to do: need to calculate each time the BPM changes the times of each
                             of the 6 notes after it, so their decon and constr. times
                             can be calculate
            */
            qDebug() << measureBPM << "bpm";

            note_mSPB = 1/(measureBPM/60000); //Beats per millisecond
            double arrowTime = (6/distance)*note_mSPB; //how long an arrow is on screen

            qDebug() << note_mSPB << "Milliseconds per beat";


            double noteTime = note_mSPB/divisionFactor;//gives each indiv. line of 0000 or xxxx a time.
                                                       //this is used for finding how much time each note gets

	    //The distance of the screen (not arbitrary)
	    //The speed (arbitrary) at which it is traveling
	    //creationTime = deconstructionTime - distance/speed

	    double deconTime = noteTime+totalTime;
	    qDebug() << deconTime << " decon";
	    this->destructionTime->append(deconTime);
	    totalTime+=noteTime; //Add in note to totalTime
            qDebug() << totalTime << " is song length so far";

            QList<int>* noteData = measureData->at(w);
            qDebug() << "not here";
            for(int z = 0; z < noteData->size(); z++) //this code handles hold notes. it finds the start and
            {                                         //stop times, then figures the distance
                qDebug() << "maybe here?";
                qDebug() << noteData->at(z);
                if(noteData->at(z) == 2)
                {
                    qDebug() << "can you get in?";
                    holdCounters->at(z)->append(deconTime);
                }
                else if(noteData->at(z) == 3)
                {
                    qDebug() <<"FINISH HIM!!!";
                    double endTimeHold = deconTime;
                    qDebug() << endTimeHold << " is when the hold should end";
                    double startTime = holdCounters->at(z)->last();
                    double totalHoldTime = endTimeHold - startTime;
                    qDebug() << totalHoldTime << " is how long the hold lasts";
                    int indexHold = holdCounters->at(z)->lastIndexOf(startTime);
                    qDebug() << indexHold << " is the index of the hold";
                    double holdDistance = (1/arrowTime)*totalHoldTime;
                    qDebug() << holdDistance << " is how long the hold is in pixels";
                    holdCounters->at(z)->replace(indexHold,holdDistance);
                }
            }

            this->creationTime->append(deconTime-((deconTime-lastDeconTime)-(distance/arrowTime)));
            qDebug() << (deconTime-((deconTime-lastDeconTime)-(distance/arrowTime))) << " create";
	    lastDeconTime = deconTime;
            qDebug() << lastDeconTime << " is teh last decon time";
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
