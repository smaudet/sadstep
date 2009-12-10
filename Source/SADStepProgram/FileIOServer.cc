#include "FileIOServer.h"
#include <QString>
#include "SMFileReader.h"
#include <QtDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QListIterator>

FileIOServer::FileIOServer() {
    this->catalog = SongCatalogue::getInstance();
}

const SongCatalogue* const FileIOServer::getSongCatalogue() {
    return catalog;
}

StepReader* FileIOServer::getStepReader(QString& location) {
    checkStepReaders(location); //TODO Thread Safe?
    return stepReaders[location];
}

SongReader* FileIOServer::getSongReader(QString& location) {
    checkSongReaders(location); //TODO Thread Safe?
    return songReaders[location];
}

//Returns true if a reader exists already, false otherwise
bool FileIOServer::checkStepReaders(QString& location) {
    if(stepReaders.contains(location)){
	return true;
    } else {
	if(location.endsWith(".sm",Qt::CaseInsensitive)){//Need proper file plugin sys
	    SMFileReader* sm = new SMFileReader(location);
	    songReaders.insert(location,sm);
	    stepReaders.insert(location,sm);
	} else {
	    //TODO Throw error
	    qDebug() << "------------------------------------------";
	    qDebug() << "Not a compatible file";
	    qDebug() << "------------------------------------------";
	}
	return false;
    }
}

//Returns true if a reader exists already, false otherwise
bool FileIOServer::checkSongReaders(QString& location) {
    if(songReaders.contains(location)){
	return true;
    } else {
	if(location.endsWith(".sm",Qt::CaseInsensitive)){//Need proper file plugin sys
	    SMFileReader* sm = new SMFileReader(location);
	    songReaders.insert(location,sm);
	    stepReaders.insert(location,sm);
	} else {
	    //TODO Throw error
	    qDebug() << "------------------------------------------";
	    qDebug() << "Not a compatible file";
	    qDebug() << "------------------------------------------";
	}
	return false;
    }
}

QList<Skin>* FileIOServer::getSkins() {
    QDir skinDir("Skins");
    QFileInfoList skins = skinDir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    QListIterator<QFileInfo> itr(skins);
}
