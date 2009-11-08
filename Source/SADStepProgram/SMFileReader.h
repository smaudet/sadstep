#ifndef SMFILEREADER_H
#define SMFILEREADER_H

#include "StepReader.h"
#include "SongReader.h"

class SMFileReader : public StepReader, public SongReader
{
public:
    SMFileReader(QString location);
    QList<QList<QList<int>*>*>* getStepData(int difficulty=0);
    QList<double>* getBPM(int difficulty=0);
    QString getSongFile();
    //void findTags();
private:
    static const char* tagTypeNames[];
};

#endif // SMFILEREADER_H
