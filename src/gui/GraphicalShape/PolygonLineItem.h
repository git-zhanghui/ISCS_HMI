#ifndef POLYGONLINEITEM_H
#define POLYGONLINEITEM_H

#include "PointsItem.h"

class EXPORT PolygonLineItem : public PointsItem
{
    Q_OBJECT
public:
    PolygonLineItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~PolygonLineItem();

    virtual QPainterPath shape() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

protected:

};

#endif // POLYGONLINEITEM_H
