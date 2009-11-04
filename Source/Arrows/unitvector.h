#ifndef UNITVECTOR_H
#define UNITVECTOR_H

#include "point3d.h"

class UnitVector
{
public:
    UnitVector(double x,double y,double z);
    UnitVector(Point3D& point3d);
    double getX();
    double getY();
    double getZ();
private:
    double px;
    double py;
    double pz;
};

#endif // UNITVECTOR_H
