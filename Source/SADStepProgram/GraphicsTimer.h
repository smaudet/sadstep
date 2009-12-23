/*
 *  Author: Sebastian Audet
 */
#ifndef GRAPHICSTIMER_H
#define GRAPHICSTIMER_H

#include <QTimer>

/* Again this class provides a class that uses QTimer
   but is not necessarily a QTimer*/
class GraphicsTimer: public QTimer
{
public:
    GraphicsTimer(int interval, int offset = 0);
};

#endif // GRAPHICSTIMER_H
