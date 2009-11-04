#include "Arrow.h"

Arrow::Arrow(ARROW_SPEED speed, int arrowType): speed(speed)
        ,type(arrowType){ploc=0;}

Arrow::Arrow(const Arrow& arrow):speed(arrow.speed), type(arrow.type){}

const ARROW_SPEED Arrow::getSpeed() const {
    return speed;
}

const int Arrow::getType() const {
    return type;
}

const int Arrow::getPercentLoc() const {
    return ploc;
}

void Arrow::giveLocation(int percentloc) {
    ploc=percentloc;
}
