// Author: Scott Tollas
// Date Last Modified: 12/21/09
// Last Modified By: Sebastian Audet
// Purpose: To create a score from the values of hits or misses returned from the game class

#include "Score.h"
#include <QString>
#include <QDebug>

Score::Score() {
        this->Range = 1500;
        this->totalScore = 0;
        this->praise = 0;
        ok = 0;
        good = 0;
        bad = 0;
        perfect = 0;
}
void Score::scoreSingle(int perfectTime, int HumanTime) {
        displacement = perfectTime - HumanTime;
        qDebug() << perfectTime << "ptime";
        qDebug() << HumanTime << "htime";
        if (displacement <= (double)Range/3) {// score for 1/3 of max range
        score = 1000;
        combo ++;
        praise = 4;
        perfect++;
        }
        //scoring for between (1/3 and 2/3] of max range
        if ((displacement <= (((double)Range/(2.0/3))) && (displacement >
        ((double)Range/(1.0/3))))){
        score = 500;
        combo ++;
        praise = 3;
        good++;
        }
        //scoring for between (2/3 and 3/3] of max range
        if ((displacement > (double)(Range)/(2.0/3))
        && (displacement <= (double)Range)) {
        score = 250;
        combo ++;
        praise = 2;
        ok++;
        }
        if (displacement > (double)Range){
        score = 0;
        combo= 0;
        praise = 1;
        bad++;
        }
        totalScore = totalScore + score;
        qDebug() << displacement << " displacement";
        qDebug () << Range << " Range";
}
// use to retrive total accumulated score in one game session
int Score::getTotalScore() {
        return totalScore;
}

QString Score::getScore() // return score for press
{
        scoreString = score;
        return scoreString;
}
// used to set range depending on user set options default if not called is 1500
void Score::setMaxRange(int maxRange) {
        Range = (double)maxRange;
}

Score::~Score() {
}

//use for desiding what praise needs to be shown on screen
int Score::getPraise() {
        return praise;
}

//used for returning the length of a combo
int Score::getCombo() {
        return combo;
}
int Score::getNumberOfBad() {
        return bad;
}
int Score::getNumberOfGood() {
        return good;
}
int Score::getNumberOfOk() {
        return ok;
}
int Score::getNumberOfPerfect() {
        return perfect;
}
void Score::scoreHold(int humanPress, int perfectPress, int humanRelease,
                                int perfectRelease) {
        int perfectDisplacement = perfectRelease - perfectPress;
        int humanDisplacement = humanRelease - humanPress;
        score = (perfectDisplacement)*100 - (perfectDisplacement -
                                                  humanDisplacement)*100;
        totalScore = totalScore + score;
}
