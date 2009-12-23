#include "Profile.h"

Profile::Profile(QString player) //used when new profile is created and sets all saved values to defaults
{
    savedName = player;
    usedDifficulty = "normal";
    savedRange = 1000;
    savedSpeed = 3000;
}
Profile::Profile(QString player, QString difficulty, int fileRange, int fileSpeed) // used when a known profile is used sets options to saved values and high scores
{
    savedName = player;
    usedDifficulty = difficulty;
    savedRange = fileRange;
    savedSpeed = fileSpeed;
}

void Profile::setRange(int range) // used to set range for scoring based on choices in options menu
{
    savedRange = range;
}
void Profile::setSpeed (int speed) // used to store speed from options menu
{
    savedSpeed = speed;
}
int Profile::getSpeed() // used for recalling speed set by player in options menu
{
    return (savedSpeed);
}
int Profile::getRange() // used for recalling range set by player in options menu
{
    return (savedRange);
}
void Profile::setName (QString name) // used for changing the name of the profile being used
{
    savedName = name;
}
QString Profile::getName() // used to recall the name of the profile being used
{
    return(savedName);
}

void Profile::setDifficulty(QString givenDifficulty) // sets difficulty
{

    usedDifficulty = givenDifficulty;
}
QString Profile::getDifficulty() // gets difficulty
{
    return (usedDifficulty);
}
int Profile::getDifficultyValue() // gets int value of selected difficulty
{
    if (usedDifficulty == "easy")
    {
        return(0);
    }
    if(usedDifficulty == "normal")
    {
        return(1);
    }
    if(usedDifficulty == "hard")
    {
        return(2);
    }
    if(usedDifficulty == "expert")
    {
        return(3);
    }
}






