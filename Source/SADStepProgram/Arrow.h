#ifndef ARROW_H
#define ARROW_H

#define ARROW_SPEED double

class Arrow
{
public:
    Arrow(int arrowType);
    Arrow(const Arrow&);
    const int getType() const;
    const int getPercentLoc() const;
    void giveLocation(int percentloc);
private:
    ARROW_SPEED speed;
    int type;
    int ploc;
};

#endif // ARROW_H
