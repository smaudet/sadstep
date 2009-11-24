#ifndef STEPREADER_H
#define STEPREADER_H

#include <QList>

class StepReader
{
public:
    virtual QList<QList<QList<int>*>*>* getStepData(int difficulty=0) = 0;
    virtual QList<double>* getBPM(int difficulty=0) = 0;
protected:
    QString* fileName;
};

#endif // STEPREADER_H
