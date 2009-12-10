// Author: Scott Tollas
// Date Last Modified: 11/3/09
// Purpose: To create a score from the values of hits or misses returned from the game class


#ifndef SCORE_H
#define SCORE_H

#include "ScoreData.h"
#include <QString>

class Score
{
public:
    Score();
    ~Score();
    void scoreSingle(int perfectTime, int HumanTime);
    int getTotalScore();
    void setMaxRange(int maxRange);
    int getPraise();
    QString getScore();
    int getCombo();
    int getNumberOfOk();
    int getNumberOfGood();
    int getNumberOfBad();
    int getNumberOfPerfect();
    void scoreHold(int humanPress, int perfectPress, int humanRelease,int perfectRelease);
private:
    int displacement;
    int totalScore;
    int runningScore;
    int maxRange;
    double Range;
    int praise;
    int lastScore;
    int score;
    ScoreData data;
    int combo;
    int ok;
    int good;
    int bad;
    int perfect;
    QString scoreString;
};

#endif // SCORE_H
