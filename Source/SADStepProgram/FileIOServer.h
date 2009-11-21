#ifndef FILEIOSERVER_H
#define FILEIOSERVER_H

#include "StepReader.h"
#include "SongReader.h"
#include "SongCatalogue.h"
#include <QString>
#include <QMap>

class FileIOServer
{
public:
    FileIOServer();
    const SongCatalogue* const getSongCatalogue();
    StepReader* getStepReader(QString& location);
    SongReader* getSongReader(QString& location);
private:
    QMap<QString,SongReader*> songReaders;
    QMap<QString,StepReader*> stepReaders;
    bool checkStepReaders(QString& location);
    bool checkSongReaders(QString& location);
    SongCatalogue* catalog;
};

#endif // FILEIOSERVER_H
