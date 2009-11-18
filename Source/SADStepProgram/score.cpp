// Author: Scott Tollas
// Date Last Modified: 11/3/09
// Purpose: To create a score from the values of hits or misses returned from the game class

#include "score.h"
#include <QString>
#include <QDebug>

Score::Score()//:data()
{
    this->Range = 1500.00;
    this->totalScore = 0;
    this->praise = 0;
    ok = 0;
    good = 0;
    bad = 0;
    perfect = 0;
}
void Score::calculateScore(int displacement)
{
    qDebug() << displacement << " displacement";
    qDebug () << Range << " Range";

    if (displacement <= (double)Range/3)// score for 1/3 of max range
    {
	score = 1000;
	combo ++;
	praise = 4;
	perfect++;

    }

    if ( (displacement <= (((double)Range/(2.0/3))) && (displacement > ((double)Range/(1.0/3))))) // scoring for between (1/3 and 2/3] of max range
    {
	score = 500;
	combo ++;
	praise = 3;
	good++;

    }

    if ((displacement > (double)(Range)/(2.0/3)) && (displacement <= (double)Range))// scoring for between (2/3 and 3/3] of max range
    {
	score = 250;
	combo ++;
	praise = 2;
	ok++;

    }
    if (displacement > (double)Range)
    {
	score = 0;
	combo= 0;
	praise = 1;
	bad++;

    }
    totalScore = totalScore + score;

    /*
*************************************************************
    Depriciated Code
*************************************************************
 lastScore = score;
    if (lastScore == 0)
    {
	praise = 4;
	perfect++;
    }


    if (lastScore == 250)
    {
	praise == 3;
	good++;
    }
    if (lastScore == 500)
    {
	praise = 2;
	ok++;
    }
    if (lastScore == 1000)
    {
	praise = 1;
	bad++;
    }
*/

}
int Score::getTotalScore() // use to retrive total accumulated score in one game session
{
    return totalScore;
}

QString Score::getScore() // return score for press
{
    scoreString = score;
    return scoreString;
}

void Score::setMaxRange(int maxRange) // used to set range depending on user set options
{                                     // default if not called is 1500.00
    Range = (double)maxRange;
}

Score::~Score() //deconstructor need I say more....
{
    // blank
}

int Score::getPraise() // use for desiding what praise needs to be shown on screen
{
    return praise;
}

int Score::getCombo() // used for returning the length of a combo
{
    return combo;
}
int Score::getNumberOfBad()
{
    return bad;
}
int Score::getNumberOfGood()
{
    return good;
}
int Score::getNumberOfOk()
{
    return ok;
}
int Score::getNumberOfPerfect()
{
    return perfect;
}

