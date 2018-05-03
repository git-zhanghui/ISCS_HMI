#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include "AbstractGraphicsItem.h"
#include "LineItem.h"
#include "PolygonLineItem.h"
#include "PolygonShapeItem.h"
#include "RectangleItem.h"
#include "EllipseItem.h"
#include "TextItem.h"
#include "ImageItem.h"

class EXPORT GraphicsFactory
{
public:
    static GraphicsFactory * instance();
    AbstractGraphicsItem * build(const int &id);

private:
    GraphicsFactory();
};

#endif // GRAPHICSFACTORY_H
