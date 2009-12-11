#include "Arrow.h"

Arrow::Arrow(double size,int arrowType):
	type(arrowType){ploc=0;dloc=0;this->size=size;}

Arrow::Arrow(const Arrow& arrow):size(arrow.size),type(arrow.type){}

const int Arrow::getType() const {
    return type;
}

const double Arrow::getPercentLoc() const {
    return ploc;
}

void Arrow::giveLocation(double percentloc) {
    ploc=percentloc;
}

const double Arrow::getDistanceLoc() const {
    return dloc;
}

void Arrow::setDistanceLoc(double distanceLoc) {
    dloc=distanceLoc;
}

void Arrow::addToLocation(double distanceLoc) {
    dloc+=distanceLoc;
}

double Arrow::getBottomLoc() const{
    return dloc-size;
}
