#include "PolygonLineItem.h"
#include <QPainter>

PolygonLineItem::PolygonLineItem(QGraphicsItem *parent)
    : PointsItem(parent)
{
    m_shapeName = tr("折线");
    m_points.append(QPointF(0,0));
    m_path.moveTo(m_points.first());
}

PolygonLineItem::~PolygonLineItem()
{

}

QPainterPath PolygonLineItem::shape() const
{
    QPainterPathStroker stroker;
    stroker.setWidth(8);
    QPainterPath path = stroker.createStroke(m_path);
    return path;
}

void PolygonLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->save();
    painter->setPen(m_pen);
    painter->drawPath(m_path);
    painter->restore();

    if(!m_state)
    {
        painter->save();
        painter->drawLine(m_points.last(), m_tipPoint);
        painter->restore();
    }
}
