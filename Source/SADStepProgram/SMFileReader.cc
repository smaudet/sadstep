#include "SMFileReader.h"

#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QtDebug>
#include <QListIterator>
#include <QStringList>
#include <cstring>

const char* SMFileReader::tagTypeNames[] = {
    "TITLE",
    "SUBTITLE",
    "ARTIST",
    "CREDIT",
    "MUSIC",
    "SELECTABLE",
    "BACKGROUND",
    "BANNER",
    "CDTITLE",
    "OFFSET",
    "SAMPLESTART",
    "SAMPLELENGTH",
    "BPMS",
    "STOPS",
    "NOTES"
};


SMFileReader::SMFileReader(QString location)
{
    this->fileName = new QString(location);
}
//
//void SMFileReader::findTags() {
//    QFile file(fileName);/*
//    qDebug() << file.exists();*/
//    file.open(QIODevice::ReadOnly);/*
//    qDebug() << file.canReadLine();
//    qDebug() << file.fileName();
//    qDebug() << file.read(60);*/
//    QTextStream textfile(&file);
//    textfile.setCodec("UTF-8");
//    textfile.setAutoDetectUnicode(true);
//    QRegExp matcher;
//    for(int i = 0;i<sizeof(tagTypeNames);i++){
//        matcher = QRegExp("#"+QString(tagTypeNames[i])+":.*;");
//        bool found = false;
//        while(!found){
//            QString s(textfile.readLine());
//            if(s.indexOf(matcher,0)>=0){
//                qDebug() << s.indexOf(matcher,0);
//                found = true;
//            }
//        }
//    }
//}


//QString SMFileReader::getSongFile() {
//    QString s;
//        bool found = false;
//        QFile file(*fileName);
//        qDebug() << "Can open:" << file.open(QIODevice::ReadOnly);
//        while(!found) {
//            char * somedata;
//            file.readLine(somedata,10000);
//            s = somedata;
//            if(ts.startsWith("\#MUSIC:")) {
//                found = true;
//            }
//        }
//        s = s.remove(*(new QRegExp(":.*;")));
//        qDebug() << s;
//        s.truncate(s.size()-1);
//        qDebug() << s;
//        s.remove(0,1);
//        qDebug() << s;
//        return s;
//}

//TODO atm difficulty actually maps to position, and practically a
//lower number returns easier difficulty, however in future need to search in
//SM files and get the actuall difficulty
QList<QList<QList<int>*>*>* SMFileReader::getStepData(int difficulty){
    qDebug() << *fileName;
    QList<QList<QList<int>*>*>* data = new QList<QList<QList<int>*>*>();
    QFile file(*fileName);
    qDebug() << "Can open:" << file.open(QIODevice::ReadOnly);
    qDebug() << file.exists();
    qDebug() << "from the file:" << file.canReadLine();/*
    qDebug() << file.isReadable() << "Readability";
    qDebug() << file.isOpen() << "State of open";
    qDebug() << file.isTextModeEnabled() << "State of text";*/
    QTextStream textfile(&file);
    textfile.setAutoDetectUnicode(true);
    QRegExp matcher;
    matcher.setPattern("#NOTES:");
    QString lastString;
    for(int i=0;i<=difficulty;i++) {
        bool found = false;
        while(!found) {
            char * somedata;
            qDebug() << "oh noes";
            textfile.readLine();
            //file.readLine(somedata,10000);
            qDebug() << "read in line";
            QString ts(/*somedata*/textfile.readLine());
//            if(textfile.atEnd()){
//                qDebug() << "Bugged out";
//                break;
//            }
            qDebug() << "ts: " << ts;
            if(ts.startsWith("\#NOTES:")) {
                found = true;
                qDebug() << "found diff";
                lastString = ts;
            }
        }
    }
    qDebug() << "got out of header loop";
    //Skip Header info for now
    for(int i=0;i<5;i++){
        textfile.readLine();
//        char * somedata;
//        file.readLine(somedata,10000);
    }
    //Begin Reading Routine
    bool done = false;
    while(!done){
        qDebug() << "Beginning note read";
        data->append(new QList<QList<int>*>);
        QList<QList<int>*>* measure = data->last();
        bool finishedMeasure = false;
        qDebug() << "starting measure";
        while(!finishedMeasure){/*
            char * somedata;
            file.readLine(somedata,10000);*/
            QString s(/*somedata*/textfile.readLine());
            s=s.trimmed();
            //qDebug() << "file: " << s;
            if(s.isEmpty()) {
                qDebug() << "discarded empty";
                continue;
            }
            if(s.contains(",") || s.contains(";")) {
                finishedMeasure = true;
                qDebug() << "found measure";
                if(s.contains(";")){
                    qDebug() << "finished reading data";
                    done = true;
                }
            } else {
                measure->append(new QList<int>);
                QList<int>* note = measure->last();
                for(int i = 0;i<s.size();i++){
                    note->append(QString(s.at(i)).toInt());
                    qDebug() << note->last() << "s";
                }
                qDebug() << note->size();
            }
        }
    }
    qDebug() << "ought to be done with data";
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
    matcher.setPattern("#BPMS:");
    QString lastString;
    bool found = false;
    while(!found) {
        QString ts(textfile.readLine());
        if(ts.indexOf(matcher)) {
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
        QStringList vals = itr.next().split("=");
        qDebug() << vals.size();
        //Split into parts
        int ti = ((QString)vals.at(0)).toInt();
        double d = ((QString)vals.at(1)).toDouble();
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
