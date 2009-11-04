#include "timeline.h"
#include <QTimer>
#include <QList>

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
Timeline::Timeline(double bpm, QList<int>* BPM, QList<QList<int>*>* arrowData, double songLength)
{
    int dt = 0; // used as a counter in deletion proccess (see checkTime function)
    int ct = 0; // used as a counter in creation proccess (see createTime function)
    int cTime; // used it creation proccess
    int dTime; // used in destruction process
    QList <int>* creationTime;
    QList <int>* destructionTime;
    //double thisbpm = bpm;
   // double sLength = songLength;
    int x;
    for (int x=0; x < arrowData->size(); ++x)
    {
        if (arrowData->at(x)!= 0000)
        {
            // REMINDER::Arrow Creator class takes care of dealing with
            //(0000) vectors. This class ignors them.
            creationTime->append();
            //TODO: Math for creation time vector values
            destructionTime->append();
            //TODO: Math for destruction time vector values
        }
        else
        {
            // does nothing otherwise
        }



    }

}

int Timeline::getArrowSpeed()
{
    int distance;
    int arrowSpeed;

    distance = int getDistance();// size of window
    arrowSpeed = (distance/5000); // may change to include BPM @ later date
     return arrowSpeed;
}

int Timeline::timeDisplacement(pushTime)// used to send time to Score class
{
    //int getPushTime(pushTime); not needed atm
    int pushTimer = pushTime;
    int checkTime(scorePushTime);
    int displacement;
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
int TimeLine::checkTime() // returns time for destruction 1 arrow set at a time
{
    dTime = destructionTime->at(dt);
    return dTime;
    ++dt;
}
void Timeline::~Timeline() // destructor
{
}
