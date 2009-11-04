#include "unitvector.h"
#include <stdexcept>
#include <math.h>

UnitVector::UnitVector(double x,double y,double z){
    if(x<=1&x>=0&y<=1&y>=0&z<=1&z>=0){
        px=x;
        py=y;
        pz=z;
    } else {
        throw std::exception();
    }
}

UnitVector::UnitVector(Point3D& point3d){
    if(point3d.posx==0&&point3d.posy==0&&point3d.posz==0){
        throw std::exception();
    }
    double length = pow((pow(point3d.posx,2)+pow(point3d.posy,2)+pow(point3d.posz,2)),0.5);
    px=point3d.posx/length;
    py=point3d.posy/length;
    pz=point3d.posz/length;
}
