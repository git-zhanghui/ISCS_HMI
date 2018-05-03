#include "PolygonShapeItem.h"
#include <QPainter>

PolygonShapeItem::PolygonShapeItem(QGraphicsItem *parent)
    : PointsItem(parent)
{
    m_shapeName = tr("多边形");
    m_brush = QBrush(Qt::white);
    m_points.append(QPointF(0,0));
    m_path.moveTo(m_points.first());
}

PolygonShapeItem::~PolygonShapeItem()
{

}

void PolygonShapeItem::setEditComplete()
{
    m_path.closeSubpath();
    PointsItem::setEditComplete();
}

QPainterPath PolygonShapeItem::shape() const
{
    return m_path;
}

void PolygonShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->save();
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(m_path);
    painter->restore();

    if(!m_state)
    {
        painter->save();
        painter->drawLine(m_points.last(), m_tipPoint);
        painter->restore();
    }
}

void PolygonShapeItem::properties(QList<PropertyType> &properties)
{
    PointsItem::properties(properties);
    properties.append(qMakePair(m_brush.color(), tr("填充颜色")));
}

void PolygonShapeItem::updateProperty(QString propertyName, QVariant value)
{
    PointsItem::updateProperty(propertyName, value);
    if(tr("填充颜色") == propertyName)
    {
        if(value.value<QColor>() != m_pen.color())
        {
            m_brush.setColor(value.value<QColor>());
            update();
        }
    }
}
