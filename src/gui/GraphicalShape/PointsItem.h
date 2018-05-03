#ifndef POINTSITEM_H
#define POINTSITEM_H

#include "AbstractGraphicsItem.h"
#include <QPen>

class EXPORT PointsItem : public AbstractGraphicsItem
{
    Q_OBJECT
public:
    PointsItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~PointsItem();

    bool isEditComplete();
    virtual void setEditStart();
    virtual void setEditComplete();

    const QList<QPointF> points();
    void appendPoint(QPointF point);
    void setTipPoint(QPointF point);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);

private slots:
    void slot_updateGeometry();

protected:
    bool m_state;
    QPen m_pen;
    QPointF m_tipPoint;
    QPainterPath m_path;
    QList<QPointF> m_points;
};

#endif // POINTSITEM_H
