#include "FileIOServer.h"
#include <QString>
#include "SMFileReader.h"
#include <QtDebug>

FileIOServer::FileIOServer()
{
    this->catalog = SongCatalogue::getInstance();
}

const SongCatalogue* const FileIOServer::getSongCatalogue() {
    return catalog;
}

StepReader* FileIOServer::getStepReader(QString* location) {
    QString s(*location);
    qDebug() << s;
    if(s.endsWith(".sm",Qt::CaseInsensitive)) {/*
        qDebug() << "found";*/
        return new SMFileReader(*location);
    }
    return NULL;
}

SongReader* FileIOServer::getSongReader(QString* location) {
    QString s(*location);
    qDebug() << s;
    if(s.endsWith(".sm",Qt::CaseInsensitive)) {
        return new SMFileReader(*location);
    }
    return NULL;
}
