#ifndef LINEITEM_H
#define LINEITEM_H

#include "PointsItem.h"

class EXPORT LineItem : public PointsItem
{
    Q_OBJECT
public:
    LineItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~LineItem();

    virtual QPainterPath shape() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

protected:

};

#endif // LINEITEM_H
