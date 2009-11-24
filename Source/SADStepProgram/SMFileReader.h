#ifndef SMFILEREADER_H
#define SMFILEREADER_H

#include "StepReader.h"
#include "SongReader.h"
#include <QMap>

class SMFileReader : public StepReader, public SongReader {
public:
    SMFileReader(QString location);
    QList<QList<QList<int>*>*>* getStepData(int difficulty=0);
    QList<QPair<double,double>*>* getBPM(int difficulty=0);
    QString getSongFile();
    QString getBackGroundFile();
    QList<QPair<double,QString>*>* getBGAnimations(int difficulty = 0);
    QList<QPair<double,QString>*>* getMenuBGAnimations(int difficulty = 0);
    bool isMenuUsingBGAnimations(int difficulty=0);
    bool isUsingBGAnimations(int difficulty=0);
    QString getCredits();
    QList<QList<QList<int>*>*>* getNoteDataField(const char* field,
                                                 int difficulty=0);
    NotesData getNotesData(int difficutly = 0);
    double getNumericalField(const char* field,int difficulty=0);
    double getOffset(int difficulty=0);
    QString getSongArtist();
    double getSongLength();
    QString getSongLyricsPath();
    double getSongSampleLength();
    double getSongSampleStart();
    bool getSongSelectable();
    QTextStream* getSongSubtitles();
    QString getSongTitle();
    QList<QPair<double,double>*>* getStops(int difficulty=0);
    QString getSubtitle();
    QString getTransliteration(int type = 0);
    QList<double>* getVectorInfoField(const char* field,
                                      int difficulty=0);
    int getNumDifficulties();
    QString getDifficultyName(int difficulty);
protected:
private:
    QList<int>* fieldIndexes;
    void findTags();
    static const char* tagTypeNames[];
    int tagTypeNum;
    QList<QString>* songFieldData;
    QList<int>* noteIndexes;
    QList<NotesData>* notesData;
    QTextStream* textfile;
    QString wrapInDir(const QString& filename);
};

#endif // SMFILEREADER_H
