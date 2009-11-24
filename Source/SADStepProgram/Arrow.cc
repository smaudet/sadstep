#include "Arrow.h"

Arrow::Arrow(int arrowType): speed(speed)
	,type(arrowType){ploc=0;}

Arrow::Arrow(const Arrow& arrow):speed(arrow.speed), type(arrow.type){}

const int Arrow::getType() const {
    return type;
}

const double Arrow::getPercentLoc() const {
    return ploc;
}

void Arrow::giveLocation(double percentloc) {
    ploc=percentloc;
}
