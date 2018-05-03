#include "LineItem.h"
#include <QPainter>

LineItem::LineItem(QGraphicsItem *parent)
    : PointsItem(parent)
{
    m_shapeName = tr("直线");
    m_points.append(QPointF(0,0));
    m_path.moveTo(m_points.first());
}

LineItem::~LineItem()
{

}

QPainterPath LineItem::shape() const
{
    QPainterPathStroker stroker;
    stroker.setWidth(8);
    QPainterPath path = stroker.createStroke(m_path);
    return path;
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
