// Author: Scott Tollas
// Date Last Modified: 11/3/09
// Purpose: To create a score from the values of hits or misses returned from the game class

#include "score.h"

Score::Score():data()
{
    this->Range = 1500.00;
    this->totalScore = 0;
    this->praise = 0;
}
void Score::calculateScore(int displacement)
{
    if (displacement <= (1/3)*Range)// score for 1/3 of max range
    {
        score = 1000;
        combo ++;

    }

    if ( displacement <= (2/3)*Range && displacement > (1/3)* Range) // scoring for between (1/3 and 2/3] of max range
    {
        score = 500;
        combo ++;

    }

    if ( displacement > (2/3)* Range && displacement <= Range)// scoring for between (2/3 and 3/3] of max range
    {
        score = 250;
        combo ++;

    }
    else
    {
        score = 0;
        combo= 0;

    }
    totalScore = totalScore + score;
   /* because of the time delay between function calls these next lines of code till the end
      of the function are used as a mini buffer to allow a slight amount of time for the
      getPraise function to be used. while this code has no actual use in the running of
      the game it is used by the GUI classes to what to display "such as perfect or wonderful"
      when a key is pressed correcly or bad or ok when not so good as visual cues to the user
      on screen instead of trying to calculate how close he/she was because of direct score */
    lastScore = score;
    if (lastScore = 0)
    {
        praise = 4;
        perfect++;
    }


    if (lastScore = 250)
    {
        praise = 3;
        good++;
    }
    if (lastScore = 500)
    {
        praise = 2;
        ok++;
    }
    if (lastScore = 1000)
    {
        praise = 1;
        bad++;
    }


}
int Score::getTotalScore() // use to retrive total accumulated score in one game session
{
    return totalScore;
}

int Score::getScore() // return score for press
{
    return score;
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
