#ifndef POINT3D_H
#define POINT3D_H

class Point3D
{
public:
    Point3D(int x = 0,int y = 0,int z = 0);
    int posx;
    int posy;
    int posz;
    friend Point3D operator+(Point3D& p1,Point3D& p2);
    friend Point3D operator-(Point3D& p1,Point3D& p2);
};

#endif // POINT3D_H
