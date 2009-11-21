#ifndef PROFILE_H
#define PROFILE_H
#include "optionmenu.h"
#include "basemenuform.h"
#include <QString>
#include"FileIOServer.h"


class Profile
{
public:
    Profile(QString player);
    Profile(QString player,QString difficulty, int fileRange, int fileSpeed);
    void setRange(int range);
    void setSpeed(int speed);
    void setName (QString name);
    void setDifficulty (QString difficulty);
    int getRange();
    int getSpeed();
    QString getName();
    QString getDifficulty();
    int getDifficultyValue();
private:
    int savedSpeed;
    int savedRange;
    QString usedDifficulty;
    QString savedName;

};

#endif // PROFILE_H
