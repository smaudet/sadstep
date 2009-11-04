#include "GraphicsTimer.h"

GraphicsTimer::GraphicsTimer(int interval, int offset)
{
    setInterval(interval-offset);
}
