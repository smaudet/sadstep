/*
  * Author: Sebastian Audet
  *
  * The purpose of this class it to provide a way for information to about a
  * particular song to be queried. It must be noted however that classes
  * classes subclassing this class are not expected to implement working
  * versions of all these functions as some song types may not support them.
  *
  * This class is not final, however the functions will mostly stay the same.
  */

#ifndef SONGREADER_H
#define SONGREADER_H

#include "NotesData.h"
#include <QPair>
#include <QTextStream>

class SongReader {
public:
    virtual NotesData getNotesData(int difficutly = 0) = 0;
    //FIXME Decide whether or not we have just int or double
    virtual QList<QPair<double,QString>*>* getBGAnimations(int difficulty=0)=0;
    //FIXME Decide whether or not we have just int or double
    virtual QList<QPair<double,QString>*>* getMenuBGAnimations(int difficulty=0)
	    = 0;
    virtual QString getBackGroundFile() = 0;
    virtual QString getCredits() = 0;
    virtual QString getSongArtist() = 0;
    virtual QString getSongFile() = 0;
    virtual QString getSongLyricsPath() = 0;
    virtual QString getSongTitle() = 0;
    virtual QString getSubtitle() = 0;
    virtual QString getTransliteration(int type = 0) = 0;
    virtual QTextStream getSongSubtitles() = 0;
    virtual bool getSongSelectable() = 0;
    virtual bool isMenuUsingBGAnimations(int difficutly = 0) = 0;
    virtual bool isUsingBGAnimations(int difficulty = 0) = 0;
    virtual double getSongLength() = 0;
    virtual double getSongSampleLength() = 0;
    virtual double getSongSampleStart() = 0;
};

#endif // SONGREADER_H
