/*
  * Author: Sebastian Audet
  * Implementation of SongReader and StepReader that will read an sm (stepmania)
  * file
  */

#include "SMFileReader.h"

#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QtDebug>
#include <QListIterator>
#include <QStringList>
#include <QFileInfo>
#include <QDir>

const char* SMFileReader::tagTypeNames[] = {
    "TITLE",
    "SUBTITLE",
    "ARTIST",
    "TITLETRANSLIT",
    "SUBTITLETRANSLIT",
    "ARTISTTRANSLIT",
    "CREDIT",
    "BANNER",
    "BACKGROUND",
    "LYRICSPATH",
    "CDTITLE",
    "MUSIC",
    "OFFSET",
    "SAMPLESTART",
    "SAMPLELENGTH",
    "SELECTABLE",
    "BPMS",
    "STOPS",
    "BGCHANGES"
};


SMFileReader::SMFileReader(QString location) {
    fileName = new QString(location);
    songFieldData = new QList<QString>;
    notesData = new QList<NotesData>;
    fieldIndexes = new QList<int>;
    noteIndexes = new QList<int>;
    findTags();
}

//Preparses the meta data, notes meta data, and notes location
void SMFileReader::findTags() {
    //Open our file
    QFile file(*fileName);
    file.open(QIODevice::ReadOnly);
    //Use a textstream for easy parsing in Unicode
    textfile = new QTextStream(&file);
    textfile->setAutoDetectUnicode(true);
    //Find all the header info
    for(int i = 0;i<sizeof(tagTypeNames);i++){
	//Must find the entire data field
	QRegExp matcher = QRegExp(QString("#")+QString(tagTypeNames[i])+":.*;");
	QString s;
	bool found = false;
	while(!found){
	    s+=textfile->readLine();
	    int tint = s.indexOf(matcher,0);
	    if(tint>=0){
		//Add our line
		songFieldData->append(s);
		qDebug() << s;
		fieldIndexes->append(textfile->pos()+tint); //Necessary?
		qDebug() << fieldIndexes->last();
		found = true;
	    }
	}
    }
    //Find the notes locations and load the NotesData objects
    QRegExp matcher = QRegExp(QString("#")+QString("NOTES")+":");
    while(!textfile->atEnd()){
	QString s(textfile->readLine());
	int tint = s.indexOf(matcher,0);
	if(tint>=0){
	    //Found our index
	    noteIndexes->append(textfile->pos()+tint);
	    qDebug() << noteIndexes->last();
	    s = textfile->readLine();
	    //Clean space FIXME for whitespace
	    while(s.isEmpty()){
		s = textfile->readLine();
	    }
	    //TODO Generalize and implement: Placeholder for NotesData creation
	    for(int i=0;i<4;i++){
		textfile->readLine();
	    }
	    notesData->append(NotesData());
	}
    }
}


QString SMFileReader::getBackGroundFile() {

}
QList<QPair<double,QString>*>* SMFileReader::getBGAnimations(int difficulty){}
QList<QPair<double,QString>*>* SMFileReader::getMenuBGAnimations(int difficulty){}
bool SMFileReader::isMenuUsingBGAnimations(int difficulty){}
bool SMFileReader::isUsingBGAnimations(int difficulty){}
QString SMFileReader::getCredits(){}
QList<QList<QList<int>*>*>* SMFileReader::getNoteDataField(const char* field,
							   int difficulty){}
NotesData SMFileReader::getNotesData(int difficutly){}
double SMFileReader::getNumericalField(const char* field,int difficulty){}
double SMFileReader::getOffset(int difficulty){}
QString SMFileReader::getSongArtist(){}
double SMFileReader::getSongLength(){}
QString SMFileReader::getSongLyricsPath(){}
double SMFileReader::getSongSampleLength(){}
double SMFileReader::getSongSampleStart(){}
bool SMFileReader::getSongSelectable(){}
QTextStream SMFileReader::getSongSubtitles(){}
QString SMFileReader::getSongTitle(){}
QList<double>* SMFileReader::getStops(int difficulty){}
QString SMFileReader::getSubtitle(){}
QString SMFileReader::getTransliteration(int type){}
QList<double>* SMFileReader::getVectorInfoField(const char* field,
						int difficulty){}
int SMFileReader::getNumDifficulties() {}
QString SMFileReader::getDifficultyName(int difficulty) {}


QString SMFileReader::getSongFile() {
    QString s;
    bool found = false;
    QFile file(*fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream textfile(&file);
    textfile.setAutoDetectUnicode(true);
    while(!found) {
	s = textfile.readLine();
	if(s.startsWith("#MUSIC:")) {
	    found = true;
	}
    }
    s = s.remove(0,7);
    qDebug() << s;
    s.remove(s.length()-1,1);
    qDebug() << s;
    //Need to put the name relative to the sm file
    QFileInfo fi(*fileName);
    s=fi.dir().path()+"/"+s; //TODO make platform independent
    qDebug() << s;
    return s;
}

//TODO atm difficulty actually maps to position, and practically a
//lower number returns easier difficulty, however in future need to search in
//SM files and get the actuall difficulty
QList<QList<QList<int>*>*>* SMFileReader::getStepData(int difficulty){
    //qDebug() << *fileName;
    QList<QList<QList<int>*>*>* data = new QList<QList<QList<int>*>*>();
    QFile file(*fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream textfile(&file);
    textfile.setAutoDetectUnicode(true);
    QRegExp matcher;
    matcher.setPattern("#NOTES:");
    QString lastString;
    for(int i=0;i<=difficulty;i++) {
	bool found = false;
	while(!found) {
	    //textfile.readLine();
	    //file.readLine(somedata,10000);
	    //qDebug() << "read in line";
	    QString ts(/*somedata*/textfile.readLine());
	    qDebug() << "ts: " << ts;
	    if(ts.startsWith("#NOTES:")) {
		found = true;
		//qDebug() << "found diff";
		lastString = ts;
	    }
	}
    }
    //qDebug() << "got out of header loop";
    //Skipping Header info for now
    for(int i=0;i<5;i++){
	textfile.readLine();
    }
    //Begin Reading Routine
    bool done = false;
    while(!done){
	//qDebug() << "Beginning note read";
	data->append(new QList<QList<int>*>);
	QList<QList<int>*>* measure = data->last();
	bool finishedMeasure = false;
	//qDebug() << "starting measure";
	while(!finishedMeasure){
	    QString s(textfile.readLine());
	    s=s.trimmed();
	    if(s.isEmpty()) {
		//qDebug() << "discarded empty";
		continue;
	    }
	    if(s.contains(",") || s.contains(";")) {
		finishedMeasure = true;
		//qDebug() << "found measure";
		if(s.contains(";")){
		    qDebug() << "finished reading data";
		    done = true;
		}
	    } else {
		measure->append(new QList<int>);
		QList<int>* note = measure->last();
		for(int i = 0;i<s.size();i++){
		    note->append(QString(s.at(i)).toInt());
		    //qDebug() << note->last() << "s";
		}
		//qDebug() << note->size();
	    }
	}
    }
    //qDebug() << "ought to be done with data";
    return data;
}

//There happens to be only a single bpm despite the difficulty for .sm files
QList<double>* SMFileReader::getBPM(int difficulty) {
    QList<double>* data = new QList<double>;
    QFile file(*fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream textfile(&file);
    textfile.setCodec("UTF-8");
    textfile.setAutoDetectUnicode(true);
    QRegExp matcher;
    matcher.setPattern("BPMS:");
    qDebug() << matcher.pattern();
    QString lastString;
    bool found = false;
    while(!found) {
	QString ts(textfile.readLine());
	qDebug() << ts;
	if(ts.indexOf(matcher)>0) {
	    found = true;
	    lastString = ts;
	}
    }
    lastString.remove(lastString.size()-1,1);
    QStringList list = lastString.split(",");
    qDebug() << list.size();
    //Now we have extracted our data,
    //time to proof it and insert it into our
    //return value
    QListIterator<QString> itr(list);
    int index = 0;
    //TODO Perform sanity checking on data
    while(itr.hasNext()){
	QStringList vals = itr.next().split(QRegExp("="));
	qDebug() << vals.size();
	//Split into parts
	qDebug() << vals.at(0);
	int ti = ((QString)vals.at(0)).toInt();
	qDebug() << ti << "int part";
	double d = ((QString)vals.at(1)).toDouble();
	qDebug() << d << "double part";
	if(ti==index) {
	    data->append(d);
	} else {
	    //Massaging "extra" data in
	    int diff = ti-index;
	    //Off-by-one error
	    for(int i=0;i<=diff;i++){
		data->append(d);
	    }
	}
	index = ++ti;
    }
    return data;
}
