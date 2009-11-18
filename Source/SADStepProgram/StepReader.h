 /*
  * Author: Sebastian Audet
  *
  * The purpose of this class it to provide a way for information to about a
  * particular song to be queried. It must be noted however that classes
  * classes subclassing this class are not expected to implement working
  * versions of all these functions as some song types may not support them.
  *
  * This class is not final, however the functions will mostly stay the same.
  */

#ifndef STEPREADER_H
#define STEPREADER_H

#include <QList>

class StepReader
{
public:
    virtual QList<QList<QList<int>*>*>* getStepData(int difficulty=0) = 0;
    virtual QList<double>* getBPM(int difficulty=0) = 0;
    virtual QList<double>* getStops(int difficulty=0) = 0;
    virtual double getOffset(int difficulty=0)=0;
    //The following functions are experimental and may be removed in the future
    //The idea is to provide an interface for obtaining arbitrary fields
    virtual double getNumericalField(const char* field,int difficulty=0) = 0;
    virtual QList<double>* getVectorInfoField(const char* field,
					      int difficulty=0)=0;
    virtual QList<QList<QList<int>*>*>* getNoteDataField(const char* field,
							 int difficulty=0) = 0;
    virtual int getNumDifficulties() = 0;
    virtual QString getDifficultyName(int difficulty) = 0;
protected:
    QString* fileName;
};

#endif // STEPREADER_H
