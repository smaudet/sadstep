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
#include <QStringListIterator>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QTime>
#include <QVariant>

//Represents a list of tags in the most likely order
const char* SMFileReader::tagTypeNames[] = {
    "TITLE",                            //0
    "SUBTITLE",                         //1
    "ARTIST",                           //2
    "TITLETRANSLIT",            //3
    "SUBTITLETRANSLIT",         //4
    "ARTISTTRANSLIT",           //5
    "CREDIT",                           //6
    "BANNER",                           //7
    "BACKGROUND",                       //8
    "LYRICSPATH",                       //9
    "CDTITLE",                          //10
    "MUSIC",                            //11
    "OFFSET",                           //12
    "GENRE",                            //13
    "SAMPLESTART",                      //14
    "SAMPLELENGTH",                     //15
    "SELECTABLE",                       //16
    "BPMS",                                     //17
    "STOPS",                            //18
    "BGCHANGES"                         //19
};

SMFileReader::SMFileReader(QString location) {
    fileName = new QString(location);
    songFieldData = new QList<QString>;
    notesData = new QList<NotesData>;
    noteIndexes = new QList<int>;
    tagTypeNum = 20; //TODO Needs to be dynamic
    findTags();
}

//Preparses the meta data, notes meta data, and notes location
void SMFileReader::findTags() {
    //TODO Handle extremly large files
    //Open our file
    QFile file(*fileName);
    file.open(QIODevice::ReadOnly);
    //Use a textstream for easy parsing in Unicode
    textfile = new QTextStream(&file);
    textfile->setAutoDetectUnicode(true);

    //Find all the header info
    QString headertxt;
    bool found = false;
    int tint = 0;
    QString s;
    QRegExp noteMatcher(QString("#")+QString("NOTES")+":");
    QRegExp commentsMatcher(QString("//.*"));
    //Grabs all the header info before it hits NOTES tag
    while(!found&&!textfile->atEnd()) {
	s = textfile->readLine();
	tint = s.indexOf(noteMatcher,0);
	if(tint>=0) {
	    //qDebug() << "found notes";
	    found = true;
	} else {
	    //Remove Comments
	    s.remove(commentsMatcher); //TODO Perfomance issue?
	    //qDebug() << "read in line" << s;
	    headertxt+=s;
	}
    } //Works in theory
    //qDebug() << headertxt;

    //Only makes sense to parse anything if notes exist
    if(found){ //If we found something then we have notes
	//Find the notes locations and load the NotesData objects
	//TODO Skipping Header info for now
	//TODO Hard coded
	for(int i=0;i<5;i++){
	    textfile->readLine();
	}
	QString ts;
	while(ts.isEmpty()){
	    ts = textfile->readLine();
	    ts.remove(commentsMatcher); //TODO Perfomance issue?
	    ts.trimmed();
	}
	noteIndexes->append(tint+textfile->pos());

	//Continue to find notes till we end the file
	while(!textfile->atEnd()){ //TODO Throw an error here?
	    s = textfile->readLine();
	    tint = s.indexOf(noteMatcher,0);
	    if(tint>=0){ //Found #Note: tag
		//TODO Skipping Header info for now
		//TODO Hard coded
		for(int i=0;i<5;i++){
		    textfile->readLine();
		}
		QString ts1;
		while(ts1.isEmpty()){
		    ts1 = textfile->readLine();
		    ts1.remove(commentsMatcher); //TODO Perfomance issue?
		    ts1.trimmed();
		}
		noteIndexes->append(tint+textfile->pos());
	    }
	    //Find Find Info
	};

	QList<QRegExp>* regexps = new QList<QRegExp>();
	//Load tags into RegExp
	for(int i = 0;i<tagTypeNum;i++){
	    regexps->append(QRegExp(QString("#")+QString(tagTypeNames[i])+
				    ":[^;]*;"));
	}
	QListIterator<QRegExp> itr(*regexps);
	QRegExp tagRipper(QString("#")+".*:");
	while(itr.hasNext()){
	    const QRegExp& rexp = itr.next();
	    rexp.indexIn(headertxt);
	    QString tfield = rexp.cap();
	    tfield.remove(tagRipper); //Remove #TAG:
	    tfield.remove(tfield.length()-1,1); //Remove ";"
	    // << tfield << " Captured";
	    songFieldData->append(tfield);
	}
    } else {
	//TODO Throw an error
	qDebug() << "---------------------------------------------------";
	qDebug() << "ERROR WITH FILE - NO NOTES PRESENT";
	qDebug() << "---------------------------------------------------";
    }
}

QString SMFileReader::getBackGroundFile() {
    return this->songFieldData->at(8);
}
QList<QPair<double,QString>*>* SMFileReader::getBGAnimations(int difficulty){
    QStringList data = songFieldData->at(19).split(",",
						    QString::SkipEmptyParts);
    QList<QPair<double,QString>*>* rdata = new QList<QPair<double,QString>*>;
    QStringListIterator itr(data);
    int divider = 0;
    while(itr.hasNext()){
	QString field(itr.next());
	QPair<double,QString>* pair = new QPair<double,QString>;
	divider = field.indexOf("=",0);
	pair->first = field.left(divider).toDouble();
	pair->second = field.mid(divider);
	rdata->append(pair);
    }
    return rdata;
}
QList<QPair<double,QString>*>* SMFileReader::getMenuBGAnimations(int difficulty)
{
    return NULL; //Unsupported in SM files
}
bool SMFileReader::isMenuUsingBGAnimations(int difficulty){
    return false; //Unsupported in SM files
}
bool SMFileReader::isUsingBGAnimations(int difficulty){
    return songFieldData->at(19).isEmpty();
}
QString SMFileReader::getCredits(){
    return songFieldData->at(6);
}
QList<QList<QList<int>*>*>* SMFileReader::getNoteDataField(const char* field,
							   int difficulty){
    if(QString::compare(field,"NOTES")==0){
	return getStepData(difficulty);
    }
    return NULL;
}
NotesData SMFileReader::getNotesData(int difficutly){
    return notesData->at(difficutly);
}
//Funcion unsupported
double SMFileReader::getNumericalField(const char* field,int difficulty){
    //TODO Implement
    return 0;
}
double SMFileReader::getOffset(int difficulty){
    return songFieldData->at(12).toDouble();
}
QString SMFileReader::getSongArtist(){
    return songFieldData->at(2);
}
//Function unsupported
double SMFileReader::getSongLength(){
    return 0;
}
QString SMFileReader::getSongLyricsPath(){
    return wrapInDir(songFieldData->at(9));
}
double SMFileReader::getSongSampleLength(){
    return songFieldData->at(15).toDouble();
}
double SMFileReader::getSongSampleStart(){
    return songFieldData->at(14).toDouble();
}
bool SMFileReader::getSongSelectable(){
    return QVariant(songFieldData->at(16)).toBool();
}
QTextStream* SMFileReader::getSongSubtitles(){
    return new QTextStream(new QFile(getSongLyricsPath()));
}
QString SMFileReader::getSongTitle(){
    return songFieldData->at(0);
}
QList<QPair<double,double>*>* SMFileReader::getStops(int difficulty){
    QList<QPair<double,double>*>* stops = new QList<QPair<double,double>*>;
    const QString& data = songFieldData->at(17);
    QStringList list = data.split(",");
    QListIterator<QString> itr(list);
    //TODO Perform sanity checking on data
    while(itr.hasNext()){
	QStringList vals = itr.next().split(QRegExp("=")); //size = 2
	QPair<double,double>* pair = new QPair<double,double>;
	pair->first = vals.at(0).toDouble(); //beat index
	pair->second = vals.at(1).toDouble(); //stop length
	stops->append(pair);
    }
    return stops;
}
QString SMFileReader::getSubtitle(){
    return songFieldData->at(1);
}
QString SMFileReader::getTransliteration(int type){
    return ""; //TODO Implement
}
QList<double>* SMFileReader::getVectorInfoField(const char* field,
						int difficulty){
    return NULL; //TODO Implement
}
int SMFileReader::getNumDifficulties() {
    return noteIndexes->size();
}
QString SMFileReader::getDifficultyName(int difficulty) {
    return "I don't know the difficulty yet"; //TODO Implement
}



QString SMFileReader::getSongFile() {
    return wrapInDir(songFieldData->at(11));
}

//TODO atm difficulty actually maps to position, and practically a
//lower number returns easier difficulty, however in future need to search in
//SM files and get the actuall difficulty
QList<QList<QList<int>*>*>* SMFileReader::getStepData(int difficulty){
    qDebug() << "got in";
    QList<QList<QList<int>*>*>* data = new QList<QList<QList<int>*>*>();
    QFile file(*fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream textfile(&file);
    textfile.setAutoDetectUnicode(true);
    textfile.seek(noteIndexes->at(difficulty));
    //Begin Reading Routine
    bool done = false;
    while(!done){
        qDebug() << "in loop";
	QList<QList<int>*>* measure = new QList<QList<int>*>;
	data->append(measure);
	bool finishedMeasure = false;
        qDebug() << "starting measure";
	while(!finishedMeasure){
	    QString s(textfile.readLine());
	    s=s.trimmed();
	    if(s.isEmpty()) {
                qDebug() << "discarded empty";
		continue;
	    }
	    done = s.contains(";");
	    if(s.contains(",") || done) {
		finishedMeasure = true;
	    } else {
		QList<int>* note = new QList<int>;
		measure->append(note);
		for(int i = 0;i<s.size();i++){ //Split the note into parts
		    note->append(QString(s.at(i)).toInt());
		}
	    }
	}
    }
    //qDebug() << "ought to be done with data";
    return data;
}

//There happens to be only a single bpm despite the difficulty for .sm files
QList<QPair<double,double>*>* SMFileReader::getBPM(int difficulty) {
    QList<QPair<double,double>*>* bpms = new QList<QPair<double,double>*>;
    const QString& data = songFieldData->at(17);
    QStringList list = data.split(",");
    QListIterator<QString> itr(list);
    //TODO Perform sanity checking on data
    while(itr.hasNext()){
	QStringList vals = itr.next().split(QRegExp("=")); //size = 2
	QPair<double,double>* pair = new QPair<double,double>;
	pair->first = vals.at(0).toDouble(); //beat index
	pair->second = vals.at(1).toDouble(); //bpm
	bpms->append(pair);
    }
    return bpms;
}

QString SMFileReader::wrapInDir(const QString& filename){
    QString s = filename;
    QFileInfo fi(*fileName);
    s=fi.dir().path()+"/"+s;
    qDebug() << s;
    return s;
}
