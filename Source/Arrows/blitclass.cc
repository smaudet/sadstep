#include "blitclass.h"

BlitClass::BlitClass(QImage* background,QImage* arrow):surface(new QWidget()){
    this->background = background;
    this->arrow = arrow;
    this->arrows = new QList<Arrow>();
}

void BlitClass::addArrow(const Arrow& arrow){
    arrows->append(arrow);
}
