#ifndef TIMELINE_H
#define TIMELINE_H
#include <QList>

class Timeline
{
public:
    Timeline();
    Timeline(QList<QPair<double,double>*>* BPM, QList<QList<QList<int>*>*>* arrowData
                       , double songLength, double distance, double speed);

    int getArrowSpeed();
    int timeDisplacement(int pushTimer);
    int createTime();
    int checkTime();
    double getBPMChanges();
    void getNotes(QList<QList<QList<int>*>*>* arrowData);
    ~Timeline();
    void setDistance(int distance);
    QList <int>* creationTime;
    QList <int>* destructionTime;
    QList<QList<int>*>* arrowGiantMeasure;
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
};

#endif // TIMELINE_H
