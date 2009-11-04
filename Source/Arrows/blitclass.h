#ifndef BLITCLASS_H
#define BLITCLASS_H

#include <QList>
#include <QImage>
#include <QWidget>
#include "arrow.h"

class BlitClass
{
public:
    BlitClass(QImage* background = NULL,QImage* arrow = NULL);
    QImage* background;
    QImage* arrow;
    QWidget* surface;
    void addArrow(const Arrow& arrow);
    void renderArrows();
private:
    QList<Arrow>* arrows;
};

#endif // BLITCLASS_H
