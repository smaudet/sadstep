/**
  * @author Daniel Wiehe
  * @author Sebastian Audet
  * @modified 12/21/09
  */

#include <QTimer>
#include <QList>
#include <QtDebug>
#include <QPair>
#include "Timeline.h"
#include "GameCanvas.h"
#include "FileIOServer.h"
#include <cmath>

//Not only should this not happen, we don't WANT it to happen. - Sebastian Audet
//Timeline::Timeline(){
//    // shouldn't happen
//}

//TODO Stop functionality, Hold functionality, Mine functionality
//FIXME MultiBPM support
Timeline::Timeline(QList<QPair<double,double>* >* BPM,
                   QList<QList<QList<int>*>*>* arrowData,double songLength,
                   double distance, double speed, double offset) {
    double totalTime = 0;
    double lastDeconTime = 0;
    double errorsize = 0;
    double beatCounter = 0;
    double measureBPM = 0;
    double note_mSPB = 0; //note's milliseconds per beat
    creationTime = new QList<double>;
    destructionTime = new QList<double>;
    bpmChanges = new QList<double>;
    speedChanges = new QList<double>;
    holdCounters = new QList<QList<double>*>;
    new FileIOServer;

    //Initializes holdCounters to have n=arrowData->size() different QLists for
    //each lane
    for(int u=0; u<arrowData->size(); ++u) {
        QList<double>* temp = new QList<double>;
        holdCounters->append(temp);
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //----------------------- SINGLE BPM CODE ONLY----------------------------
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //Formula for note times - EDIT BUT DO NOT DELETE - Sebastian Audet
    //Destruction times; last_note_destruct_time + current_note_time;
    //Construction times SINGLE BPM; current destruct time-(arrow speed
    // * distance)
    //Construction times MULTI BPM; #1 Calculate first Construct time
    //#2 Calculate subsequent construct times
    //To calculate subsequent construct times: (Assuming atomic speeds)
    //lastConTime + (distance to next note / arrow speed) = nextConTime

    /*
     * need to do: need to calculate each time the BPM changes the times
     * of each of the 6 notes after it, so their decon and constr. times
     * can be calculated
     */

    //First we must calculate things like speed, etc.

    //---------------------------BPM Code---------------------------

    //Load the BPM
    //FIXME Single BPM, also misleading variable name
    measureBPM = BPM->at(0)->second;//loads in the initial BPM
    //Making sure that the BPM is changed i.e. set at the beginning of the song
    bpmChanges->append(0);
    //gives (pixels/measure)*(beats/second)*(1 measure/4 beats)
    //gives (pixels/seconds) = pixels per second
    //FIXME Single speed
    speedChanges->append((distance/6)*(measureBPM/60.0)*(0.25));
    //totalTime = (offset-(2*offset))*1000; //adds in the song's offset.
    //qDebug() << totalTime << " should include offset";
    //Whether the offset has been set
    bool bpmOffsetSet = false;
    //Global Offset for negative creation times
    int createOffset = 0;

    //Debug progress
    //qDebug() << measureBPM << "measureBPM";
    //qDebug() << speedChanges->last() << "speedChanges->last()";

    //Now we must go in and calculate the measure stuff

    for(int x=0;x < arrowData->size();x++) {
        //Eg:
        //0 0 0 1
        //1 0 0 2
        //0 0 1 0
        //0 0 0 3
        //Does not ignore zero vectors since they are still counted in the game


        //Calculate the time division for this measure


        QList<QList<int>*>* measureData = arrowData->at(x);
        double measureSize = measureData->size();
        /* For 8/4 time we'd get 2, 4/4 would be 1, so we have the factor of
         * division, a ratio of notes per measure to beats per measure, or of
         * notes to beats, within a measure
         */
        double divisionFactor = measureSize/4;

        //Loop over the measure notes and assign times to notes
        for(int w = 0; w < measureData->size(); w++) {

            //This keeps track of how many beats have occured
            //(beats/ 1 note)
            beatCounter += 1/divisionFactor;

            //--------------------IGNORE CODE------------------------------
            //this is ignored if there is only one BPM
            for(int y = 1; y < BPM->size(); ++y) {//FIXME May break if used
                QPair<double,double>* bpmInfo = BPM->at(y);
                if (beatCounter > bpmInfo->first)//used if multiple BPMs exist
                {
                    measureBPM = BPM->at(y+1)->second; //this reads in the next bpm. It then increments y,
                    //the exits the loop
                    bpmChanges->append(lastDeconTime);
                    double theSpeedChange = ((distance/6)*(measureBPM/60));//pixels per 6 beats times beats per
                    speedChanges->append(theSpeedChange);                  //minute times 1 minute per 60 seconds
                }                                                          //therefore theSpeedChange is pixels per second
                else
                {break;}//used most of the time. happens when beatCounter isn't at the BPM change yet.
            }
            //-------------------END IGNORE CODE---------------------------

            note_mSPB = 1/(measureBPM/60000); //In milliseconds per 1 beat
            //how long an arrow is on screen in milliseconds/pixels
            //measure/pixels * mseconds / beat * 4 beats/ 1 measure
            double arrowTime = (6/distance)*note_mSPB*4;

            //Gives each indiv. line of 0000 or xxxx a time. This is used for
            //finding how much time each note gets.
            //(milliseconds/beat)/(notes/beat) = (milliseconds/note)
            double noteTime = note_mSPB/divisionFactor;

            totalTime+=noteTime; //Add in note to totalTime
            double deconTime = totalTime;

            //-------------------------IGNORE CODE----------------------------
            QList<int>* noteData = measureData->at(w);
            //This code handles hold notes. it finds the start and stop times,
            //then figures the distance.
            for(int z = 0; z < noteData->size(); z++) { //FIXME Probably broken
                if(noteData->at(z) == 2) {
                    holdCounters->at(z)->append(deconTime);
                } else if(noteData->at(z) == 3) {
                    double endTimeHold = deconTime;
                    //qDebug() << endTimeHold << "is when the hold should end";
                    double startTime = holdCounters->at(z)->last();
                    double totalHoldTime = endTimeHold - startTime;
                    //qDebug() << totalHoldTime << "is how long the hold lasts";
                    int indexHold = holdCounters->at(z)->lastIndexOf(startTime);
                    //qDebug() << indexHold << " is the index of the hold";
                    double holdDistance = (1/arrowTime)*totalHoldTime;
                    //qDebug() << holdDistance << "is pixel length";
                    holdCounters->at(z)->replace(indexHold,holdDistance);
                }
            }
            //-----------------------END IGNORE CODE--------------------------

            //FIXME SINGLE BPM ONLY
            //The distance of the screen (not arbitrary)
            //The speed (arbitrary) at which it is traveling
            //creationTime = deconstructionTime - distance/speed
            //(pixels)/(pixels/second) = seconds
            //seconds*(1000 mseconds/seconds) = mseconds;
            int createT = deconTime-((distance/speedChanges->last())*1000.0);

            //Check the data
            //qDebug() << distance << "distance";
            //qDebug() << speedChanges->last() << "speed";
            //qDebug() << createT << "createTimeInit";

            //Push creation times out of the negative
            if(createT<0&&!bpmOffsetSet){
                createOffset = -createT;
                bpmOffsetSet = true;
            }

            //Finally chuck our creationTime into the queue with an offset >=0
            this->creationTime->append(createOffset+createT);

            lastDeconTime = deconTime;
            this->destructionTime->append(deconTime+createOffset);


            //Check the data
            //qDebug() << createOffset << "offset";
            //qDebug() << createT << "orignal create time";
            //qDebug() << this->creationTime->last() << "create time";
            qDebug() << destructionTime->last() - creationTime->last() << "diff";
            //qDebug() << deconTime << "orignal destruct time";
            //qDebug() << destructionTime->last() << "destruct time";

            //Error stuff - IGNORE
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
    for (int x = 0; x < arrowData->size(); x++) {
        localMeasure = arrowData->at(x);
        arrowGiantMeasure->append(*localMeasure);
    }
    //qDebug() << "arrowGiantMeasure" << arrowGiantMeasure->size();
}
int Timeline::getArrowSpeed() {
    return arrowSpeed;
}
void Timeline::setDistance(int distance) {
    this->distance = distance;
}
int Timeline::timeDisplacement(int pushTimer) {// used to send time to Score class
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
double Timeline::createTime() {//returns creation time for arrows 1 set at a time
    cTime = creationTime->at(ct);
    return cTime;
    ++ct;
}
double Timeline::checkTime() {// returns time for destruction 1 arrow set at a time
    dTime = destructionTime->at(dt);
    return dTime;
    ++dt;
}
Timeline::~Timeline() {// destructor
    //FIXME Delete data to avoid a memory leak
}
void Timeline::calculateTimes (int speed, int distance) {
    arrowSpeed = (distance/speed);
    timelineDistance = distance;
}
