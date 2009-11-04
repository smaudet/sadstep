#include "path.h"
#include <QVectorIterator>
#include <math.h>

Path::Path(QVector<Point3D>& points): points(points)
        ,distances(new QVector<double>()),univecs(new QVector<UnitVector>()){
    QVectorIterator<Point3D> itr(points);
    /*while(itr.hasNext()){
        Point3D& p = itr.next();
        Point3D& p2;
        if(itr.hasNext()){
            p2 = itr.peekNext();
        } else {
            continue; //Last point reached.
        }
        this->distances->append(computeDistance(p,p2));
        this->univecs->append(new UnitVector(p-p2));
    }*/
}

Path::Path(Path& path): points(path.points), distances(path.distances)
        ,univecs(path.univecs){
}

void Path::addPoint(Point3D& point) {
    points.append(point);
    Point3D& p1 = points[points.size()-2];
    //Point3D& univec(p1-point);
    this->distances->append(computeDistance(p1,point));
    //this->univecs->append(new UnitVector(univec));
}

double Path::computeDistance(Point3D& p1,Point3D& p2) {
    double retval;
    retval = std::abs(p1.posx-p2.posx)+std::abs(p1.posy-p2.posy)
             +std::abs(p1.posz-p2.posz);
    return retval;
}
