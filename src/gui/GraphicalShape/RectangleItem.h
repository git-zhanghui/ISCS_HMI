#ifndef RECTANGLEITEM_H
#define RECTANGLEITEM_H

#include "AbstractRegularItem.h"

class EXPORT RectangleItem : public AbstractRegularItem
{
    Q_OBJECT
public:
    RectangleItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~RectangleItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);
};

#endif // RECTANGLEITEM_H
