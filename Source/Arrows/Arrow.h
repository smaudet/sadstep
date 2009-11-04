#ifndef ARROW_H
#define ARROW_H

#define ARROW_SPEED double

class Arrow
{
public:
    Arrow(ARROW_SPEED speed, int arrowType);
    Arrow(const Arrow&);
    const int getType() const;
    const int getPercentLoc() const;
    const ARROW_SPEED getSpeed() const;
    void giveLocation(int percentloc);
private:
    ARROW_SPEED speed;
    int type;
    int ploc;
};

#endif // ARROW_H
