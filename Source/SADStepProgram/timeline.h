#ifndef TIMELINE_H
#define TIMELINE_H
#include <QList>

class Timeline
{
public:
    Timeline();
    Timeline::Timeline(QList<double>* BPM, QList<QList<QList<int>*>*>* arrowData
		       , double songLength, double distance, double speed);
    int Timeline::getArrowSpeed();
    int Timeline::timeDisplacement(int pushTimer);
    int Timeline::createTime();
    int Timeline::checkTime();
    void Timeline::getNotes(QList<QList<QList<int>*>*>* arrowData);
    Timeline::~Timeline();
    void setDistance(int distance);
    QList <double>* creationTime;
    QList <double>* destructionTime;
    QList<QList<int>*>* arrowGiantMeasure;
    void calculateTimes(int speed, int distance);

private:
    int dt;
    int ct;
    int cTime;
    int dTime;
    int distance;
    int arrowSpeed;
    int pushTimer;
    int scorePushTime;
    int displacement;
    int timelineDistance;

};

#endif // TIMELINE_H
