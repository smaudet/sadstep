#ifndef PATH_H
#define PATH_H

#include <QVector>
#include "point3d.h"
#include "unitvector.h"

class Path
{
public:
    Path(QVector<Point3D>& points);
    Path(Path& path);
    void addPoint(Point3D& point);
    const UnitVector getUnitVector(int index);
    const double getDistance(int index);
private:
    double computeDistance(Point3D& p1, Point3D& p2);
    QVector<Point3D>& points;
    QVector<double>* distances;
    QVector<UnitVector>* univecs;
};

#endif // PATH_H
