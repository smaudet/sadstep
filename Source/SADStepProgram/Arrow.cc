#include "Arrow.h"

Arrow::Arrow(int arrowType): speed(speed)
	,type(arrowType){ploc=0;}

Arrow::Arrow(const Arrow& arrow):speed(arrow.speed), type(arrow.type){}

const int Arrow::getType() const {
    return type;
}

const int Arrow::getPercentLoc() const {
    return ploc;
}

void Arrow::giveLocation(int percentloc) {
    ploc=percentloc;
}
