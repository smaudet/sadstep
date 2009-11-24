#include "SongCatalogue.h"
#include <QStringList>
#include <QtDebug>

bool SongCatalogue::singleton = false;
SongCatalogue* SongCatalogue::singInst = NULL;

//TODO Support categorization
//TODO Support nesting
//TODO Support Music
SongCatalogue::SongCatalogue()
{
    //Explore the base directory
    this->baseDir = "Songs";
    QbaseDir = new QDir(baseDir);
    //Find the songs - in future support folders and categorization
    QFileInfoList dirs = QbaseDir
			 ->entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    QListIterator<QFileInfo> itr(dirs);
    QStringList* stepfiles = new QStringList();
    while(itr.hasNext()){
	QDir tdir(itr.next().filePath());
	QFileInfoList files = tdir.entryInfoList(QDir::Files);
	QListIterator<QFileInfo> itr2(files);
	while(itr2.hasNext()){
	    //qDebug() << itr2.peekNext().filePath();
	    stepfiles->append(itr2.next().filePath());
	}
    }
    //TODO Check for robustness
    this->list = new QList<QString>(stepfiles->filter(QRegExp("\\.sm")));
}

QString SongCatalogue::getFileName(int index) const {
    qDebug() << "zombies";
    return list->at(index);
}

const QList<QString>* const SongCatalogue::getFileNames() const{
    return list;
}

SongCatalogue* const SongCatalogue::getInstance() {
    if(!singleton) {
	SongCatalogue::singInst = new SongCatalogue();
	singleton = true;
    }
    return SongCatalogue::singInst;
}
