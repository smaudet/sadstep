#ifndef TIMELINE_H
#define TIMELINE_H
#include <QList>
#include <QPair>

class Timeline
{
public:
    Timeline();
    Timeline(QList<QPair<double,double>*>* BPM, QList<QList<QList<int>*>*>* arrowData
                       , double songLength, double distance, double speed, double offset);
    ~Timeline();
    int getArrowSpeed();
    int timeDisplacement(int pushTimer);
    double createTime();
    double checkTime();
    double getBPMChanges();
    void getNotes(QList<QList<QList<int>*>*>* arrowData);
    void setDistance(int distance);
    void calculateTimes(int speed, int distance);
    QList <double>* creationTime;
    QList <double>* destructionTime;
    QList <double>* bpmChanges;
    QList <double>* speedChanges;
    QList<QList<int>*>* arrowGiantMeasure;
    QList<QList<double>*>* holdCounters;
private:
    int dt;
    int ct;
    double cTime;
    double dTime;
    int distance;
    int arrowSpeed;
    int pushTimer;
    int scorePushTime;
    int displacement;
    int timelineDistance;
};

#endif // TIMELINE_H
