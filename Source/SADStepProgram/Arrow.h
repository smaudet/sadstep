#ifndef ARROW_H
#define ARROW_H

#define ARROW_SPEED double

class Arrow
{
public:
    Arrow(int arrowType);
    Arrow(const Arrow&);
    const int getType() const;
    const double getPercentLoc() const;
    void giveLocation(double percentloc);
private:
    ARROW_SPEED speed;
    int type;
    double ploc;
};

#endif // ARROW_H
