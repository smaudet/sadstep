/*
 * ArrowGraphicsSet.h
 *
 *  Created on: Oct 16, 2009
 *      Author: Sebastian Audet
 */

#ifndef ARROWGRAPHICSSET_H_
#define ARROWGRAPHICSSET_H_

#include <QList>
#include <QImage>

class ArrowGraphicsSet {
public:
    ArrowGraphicsSet();
    virtual ~ArrowGraphicsSet();
    //Loads the complete set
    void loadAllGraphics(int width, int height);
    //Loads just the non-arrow images
    void loadGraphics();
    //Allows the number of lanes to be specified
    void loadArrowGraphics(int width, int height, int lanes=4);
    const QImage* getArrowGraphic(int type, int lane) const;
    const QImage* getGraphic(int index) const;
private:
    QList<QList<QImage*>*>* arrowImages; //Allows for caching the arrows
    QList<QImage*>* otherImages;
};

#endif /* ARROWGRAPHICSSET_H_ */
