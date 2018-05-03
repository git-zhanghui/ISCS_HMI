#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "AbstractGraphicsItem.h"
#include <QFont>

class EXPORT TextItem : public AbstractGraphicsItem
{
    Q_OBJECT
public:
    TextItem(QGraphicsItem *parent = Q_NULLPTR);
    ~TextItem();

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);

protected:
    QPen m_pen;
    QFont m_font;
    QString m_contentText;
};

#endif // TEXTITEM_H
