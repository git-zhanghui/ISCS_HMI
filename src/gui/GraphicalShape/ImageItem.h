#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include "AbstractRegularItem.h"

class EXPORT ImageItem : public AbstractRegularItem
{
    Q_OBJECT
public:
    ImageItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~ImageItem();

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);

protected:
    QString m_imagePath;
};

#endif // IMAGEITEM_H
