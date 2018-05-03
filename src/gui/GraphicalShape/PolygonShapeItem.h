#ifndef POLYGONSHAPEITEM_H
#define POLYGONSHAPEITEM_H

#include "PointsItem.h"

class EXPORT PolygonShapeItem : public PointsItem
{
    Q_OBJECT
public:
    PolygonShapeItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~PolygonShapeItem();

    virtual void setEditComplete();

    virtual QPainterPath shape() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);

protected:
    QBrush m_brush;
};

#endif // POLYGONSHAPEITEM_H
