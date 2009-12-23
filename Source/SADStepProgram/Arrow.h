/*
 *  Author: Sebastian Audet
 */
#ifndef ARROW_H
#define ARROW_H

#define ARROW_SPEED double

class Arrow
{
public:
    Arrow(double size,int arrowType);
    Arrow(const Arrow&);
    const int getType() const;
    //Deprecated
    const double getPercentLoc() const;
    //Deprecated
    void giveLocation(double percentloc);
    void addToLocation(double distanceLoc);
    void setDistanceLoc(double distanceLoc);
    const double getDistanceLoc() const;
    double getBottomLoc() const;
private:
    double size;
    int type;
    double ploc;
    double dloc;
};

#endif // ARROW_H
