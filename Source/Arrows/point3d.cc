#include "point3d.h"

Point3D::Point3D(int x, int y, int z): posx(x), posy(y), posz(z) {}

Point3D operator+(Point3D& p1,Point3D& p2) {
    Point3D* p = new Point3D(p1.posx+p2.posx,p1.posy+p2.posy,p1.posz+p2.posz);
    //Point3D& r = &(*p);
    return *p;
}

Point3D operator-(Point3D& p1,Point3D& p2) {
    Point3D* p = new Point3D(p1.posx-p2.posx,p1.posy-p2.posy,p1.posz-p2.posz);
    //Point3D& r = &(*p);
    return *p;
}
