#ifndef ELLIPSEITEM_H
#define ELLIPSEITEM_H

#include "AbstractRegularItem.h"

class EXPORT EllipseItem : public AbstractRegularItem
{
    Q_OBJECT
public:
    EllipseItem(QGraphicsItem *parent = Q_NULLPTR);
    ~EllipseItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);
};

#endif // ELLIPSEITEM_H
