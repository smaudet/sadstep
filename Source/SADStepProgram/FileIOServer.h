#ifndef FILEIOSERVER_H
#define FILEIOSERVER_H

#include "StepReader.h"
#include "SongReader.h"
#include "SongCatalogue.h"
#include <QString>

class FileIOServer
{
public:
    FileIOServer();
    const SongCatalogue* const getSongCatalogue();
    StepReader* getStepReader(QString* location);
    SongReader* getSongReader(QString* location);
private:
    SongCatalogue* catalog;
};

#endif // FILEIOSERVER_H
