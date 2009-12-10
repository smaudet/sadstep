#ifndef SCOREEVALUATOR_H
#define SCOREEVALUATOR_H
#include <QList>
#include "score.h"

class ScoreEvaluator
{
public:
    ScoreEvaluator(QList<double>* pressTimes, QList<QList<int>*>* shouldBePressed, int givenRange);
    void evaluateSingle(QList <int>* pressed,int time);
    void evaluateHoldRelease (QList <int>* holdReleased, int holdReleaseTime);
    void evaluateHoldStart(QList <int>* holdPressed, int holdPressTime);
    void setCurrentTime(int time);

    Score* getScoreInstance();
private:
    QList<int>* lane1;
    QList<int>* lane2;
    QList<int>* lane3;
    QList<int>* lane4;
    QList<int>* locationHolder;
    QList<int>* holdStartTimes;
    QList<int> release;
    QList<int>* perfectHoldStart;
    QList<double>* perfectPressTime;
    int currentTime;
    int pressTime;
    int range;
    int overallTime;
    Score* score;
    int lane;



};

#endif // SCOREEVALUATOR_H
