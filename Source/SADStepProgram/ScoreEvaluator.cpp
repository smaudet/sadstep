//Author: Scott Tollas
//Date last Modified: 12/9/09
//Purpose: to arange note data in a way that can be incremented and scored properly


#include "ScoreEvaluator.h"
#include <iostream>
#include <QtDebug>



ScoreEvaluator::ScoreEvaluator(QList<double>* pressTimes, QList<QList<int>*>* shouldBePressed,
                               int givenRange)
{

    double appendorz = 0.0;
    perfectPressTime = new QList <double>;
    lane1 = new QList <int>;
    lane2 = new QList <int>;
    lane3 = new QList <int>;
    lane4 = new QList <int>;
    holdStartTimes = new QList <int>;
    locationHolder = new QList <int>;
    perfectHoldStart = new QList <int>;
    for(int x =0; x< shouldBePressed->size(); x++)
    {
        range = givenRange; // set range to global for class
        overallTime = 0;
        // break presses down into individual vectors based on the lane they represent
        lane1->append(shouldBePressed->at(x)->at(0));
        //qDebug() << shouldBePressed->at(x)->at(0) << " lane 1 value at " << x;
        lane2->append(shouldBePressed->at(x)->at(1));
        //qDebug() << shouldBePressed->at(x)->at(1) << " lane 2 value at " << x;
        lane3->append(shouldBePressed->at(x)->at(2));
        //qDebug() << shouldBePressed->at(x)->at(2) << " lane 3 value at " << x;
        lane4->append(shouldBePressed->at(x)->at(3));
        //qDebug() << shouldBePressed->at(x)->at(3) << " lane 4 value at " << x;
        //qDebug() << pressTimes->at(x) << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";
        appendorz = pressTimes->at(x);
        //*******************************************************************************
        // perfectPressTime->append(pressTimes->at(x); or the line after this note
        // will not allow a List size greater than 1, Need this to work and score should work correctly
        // if called correctly, however times are still way off so no scoreing will be dont even if you
        // get this to work, dealing in milliseconds hurts
        // NEED THIS TO WORK BUT LIST WONT APPEND EVEN WHEN GIVEN VALID VALUES TO DO SO
        // IF THIS IS CORRECTLY FIXED SCORING FOR SINGLES SHOULD WORK
        //                                                          Scott
        //*******************************************************************************
        perfectPressTime->append(appendorz); // set pressTimes to global for class
        //qDebug() << appendorz;
        //qDebug()<< perfectPressTime->size() << " size of perfectPressTime";

    }


        for (int u =0; u<5; u++)
        {
            holdStartTimes->append(0); // holds start values for holds in individual lanes
            locationHolder->append(0); // holds values for where in vector each with lane1 at(0)
            perfectHoldStart->append(0);


        }

}
void ScoreEvaluator::evaluateSingle(QList <int>* pressed, int time)
{ // used to evaluate a single press represented by a 1 in the pressed vector
    pressTime = time;

    //qDebug() << pressTime << " pressTime";
    for (int y=0; y<pressed->size(); y++)
    {
         //qDebug() << pressed->at(y) << " at " << y+1;
        if (pressed->at(y) ==1)
        {
            if (y==0) // check lane 1 values
            {
                if(lane1->at(locationHolder->at(y)) == 1)
                {
                    score->scoreSingle(perfectPressTime->at(locationHolder->at(y)), pressTime);
                    locationHolder->replace(y,locationHolder->at(y)+1); // increment holder as value has been scored
                }
            }
            if (y==1) // check lane 2 values
            {
                //qDebug()<< " RIVER 1";
                //qDebug()<< locationHolder->at(y);
                //qDebug()<< lane2->at(locationHolder->at(y)) << " lane value" ;

                if(lane2->at(locationHolder->at(y)) == 1)
                {
                    //qDebug()<< " RIVER 2";
                    score->scoreSingle(perfectPressTime->at(locationHolder->at(y)), pressTime);
                    //qDebug()<< " RIVER 3";
                    locationHolder->replace(y,locationHolder->at(y)+1); // increment holder as value has been scored
                    //qDebug()<< " RIVER 4";
                }

            }
            if (y==2) // check lane 3 values
            {
                if(lane3->at(locationHolder->at(y)) == 1)
                {
                    score->scoreSingle(perfectPressTime->at(locationHolder->at(y)), pressTime);
                    locationHolder->replace(y,locationHolder->at(y)+1); // increment holder as value has been scored
                }
            }
            if (y==3) // check lane 4 values
            {
                if(lane4->at(locationHolder->at(y)) == 1)
                {
                    score->scoreSingle(perfectPressTime->at(locationHolder->at(y)), pressTime);
                    locationHolder->replace(y,locationHolder->at(y)+1); // increment holder as value has been scored
                }
            }
        }
    }
}

void ScoreEvaluator::setCurrentTime(int time)
{
    // gets the time and itterates the vectors to next value if current value no longer in score range
    overallTime = time;
    do
    {
        for(int w = 0; w <5; w++)
            if(perfectPressTime->at(locationHolder->at(w))< overallTime)
            {
            //qDebug() << "REPLACEMENT COMPLETE";
            locationHolder->replace(w, locationHolder->at(w)+1);
        }
    }
    // while prevent exit until all lanes are caught up to current time
    while (perfectPressTime->at(locationHolder->at(0)) < overallTime &&
           perfectPressTime->at(locationHolder->at(1)) < overallTime &&
           perfectPressTime->at(locationHolder->at(2)) < overallTime &&
           perfectPressTime->at(locationHolder->at(3)) < overallTime);
}

void ScoreEvaluator::evaluateHoldStart(QList <int>* holdPressed, int holdPressTime)
{
    for (int y=0; y<holdPressed->size(); y++)
    {
        if (holdPressed->at(y) ==2)
        {
            if (y==0) // check lane 1 values
            {
                if(lane1->at(locationHolder->at(y)) == 2)
                {
                    holdStartTimes->replace(y ,holdPressTime);
                    perfectHoldStart->replace(y, perfectPressTime->at(locationHolder->at(y)));
                }
            }
            if (y==1) // check lane 2 values
            {
                if(lane1->at(locationHolder->at(y)) == 2)
                {
                    holdStartTimes->replace(y ,holdPressTime);
                    perfectHoldStart->replace(y, perfectPressTime->at(locationHolder->at(y)));
                }
            }
            if (y==2) // check lane 3 values
            {
                if(lane1->at(locationHolder->at(y)) == 2)
                {
                    holdStartTimes->replace(y ,holdPressTime);
                    perfectHoldStart->replace(y, perfectPressTime->at(locationHolder->at(y)));
                }
            }
            if (y==3) // check lane 4 values
            {
                if(lane1->at(locationHolder->at(y)) == 2)
                {
                    holdStartTimes->replace(y ,holdPressTime);
                    perfectHoldStart->replace(y, perfectPressTime->at(locationHolder->at(y)));
                }
            }
        }
    }
}

void ScoreEvaluator::evaluateHoldRelease (QList <int>* holdReleased, int holdReleaseTime)
{
    //TODO: implement release for holds
    for (int z=0; z<5; z++)
    {
        release.append(holdReleased->at(z));
        if (release.at(z) == 3)
        {
            lane = release.at(z);
        }
        switch(lane){
        case 0:
            {
                int tempInc = locationHolder->at(0)-1;
                do
                {
                    tempInc ++;
                }
                while (lane1->at(tempInc)!=3);
                score->scoreHold(perfectHoldStart->at(lane), holdStartTimes->at(lane), holdReleaseTime,
                                 perfectPressTime->at(tempInc));
            }
        case 1:
            {
                int tempInc = locationHolder->at(0)-1;
                do
                {
                    tempInc ++;
                }
                while (lane2->at(tempInc)!=3);
                score->scoreHold(perfectHoldStart->at(lane), holdStartTimes->at(lane), holdReleaseTime,
                                 perfectPressTime->at(tempInc));
            }

        case 2:
            {
                int tempInc = locationHolder->at(0)-1;
                do
                {
                    tempInc ++;
                }
                while (lane3->at(tempInc)!=3);
                score->scoreHold(perfectHoldStart->at(lane), holdStartTimes->at(lane), holdReleaseTime,
                                 perfectPressTime->at(tempInc));
            }

        case 3:
            {
                int tempInc = locationHolder->at(0)-1;
                do
                {
                    tempInc ++;
                }
                while (lane4->at(tempInc)!=3);
                score->scoreHold(perfectHoldStart->at(lane), holdStartTimes->at(lane), holdReleaseTime,
                                 perfectPressTime->at(tempInc));
            }
        }
    }

}

Score* ScoreEvaluator::getScoreInstance()
{
    return (score);
}






