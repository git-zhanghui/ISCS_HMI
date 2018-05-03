#ifndef ABSTRACTREGULARITEM_H
#define ABSTRACTREGULARITEM_H

#include "AbstractGraphicsItem.h"

class EXPORT AbstractRegularItem : public AbstractGraphicsItem
{
    Q_OBJECT
public:
    AbstractRegularItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~AbstractRegularItem();

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);

protected:
    void drawControlRect(QPainter *painter);

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

    virtual void updateShapeGrometry(QPointF scenePos);
    virtual void updateControlRect();
    virtual void updatePainterPath();

private slots:
    void slot_updateGeometry();

protected:
    QPen m_pen;
    QBrush m_brush;
    QPainterPath m_path;

private:
    QList<QRectF> m_controlRect;
    qint8 m_hoverPointIndex;
    qreal m_previousWidth;
    qreal m_previousHeight;
    QPainterPath m_previousPath;
};

#endif // ABSTRACTREGULARITEM_H
