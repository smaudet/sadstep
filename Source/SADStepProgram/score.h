// Author: Scott Tollas
// Date Last Modified: 11/3/09
// Purpose: To create a score from the values of hits or misses returned from the game class


#ifndef SCORE_H
#define SCORE_H

#include "ScoreData.h"
#include "score.h"

class Score
{
public:
    Score();
    ~Score();
    void calculateScore(int displacement);
    int getTotalScore();
    void setMaxRange(int maxRange);
    int getPraise();
    int getScore();
    int getCombo();
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
};

#endif // SCORE_H
