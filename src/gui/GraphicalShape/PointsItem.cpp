#include "PointsItem.h"

PointsItem::PointsItem(QGraphicsItem *parent)
    : AbstractGraphicsItem(parent),
      m_state(true),
      m_tipPoint(0.0, 0.0)
{
    connect(this, SIGNAL(geometryChanged()), this, SLOT(slot_updateGeometry()));
}

PointsItem::~PointsItem()
{

}

bool PointsItem::isEditComplete()
{
    return m_state;
}

void PointsItem::setEditStart()
{
    m_state = false;
}

void PointsItem::setEditComplete()
{
    m_state = true;
}

const QList<QPointF> PointsItem::points()
{
    return m_points;
}

void PointsItem::appendPoint(QPointF point)
{
    if(!m_state)
    {
        m_points.append(point);
        m_path = QPainterPath();
        QPolygonF polygonF;
        foreach (QPointF pf, m_points)
        {
            polygonF << pf;
        }
        m_path.addPolygon(polygonF);
    }
}

void PointsItem::setTipPoint(QPointF point)
{
    m_tipPoint = point;
}

QRectF PointsItem::boundingRect() const
{
    qreal delta = m_pen.widthF() / 2.0 + OUTLINEMARGINS * 3 * 2;
    if(m_state)
    {
        return m_path.boundingRect().adjusted(-delta, -delta, delta, delta);
    }
    else
    {
        QPainterPath path = m_path;
        path.lineTo(m_tipPoint);
        return m_path.boundingRect().adjusted(-delta, -delta, delta, delta);
    }
}

QPainterPath PointsItem::shape() const
{
    if(m_state)
    {
        return m_path;
    }
    else
    {
        QPainterPath path = m_path;
        path.lineTo(m_tipPoint);
        return path;
    }
}

void PointsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void PointsItem::properties(QList<PropertyType> &properties)
{
    AbstractGraphicsItem::properties(properties);
    properties.append(qMakePair(m_pen.color(), tr("线颜色")));
}

void PointsItem::updateProperty(QString propertyName, QVariant value)
{
    AbstractGraphicsItem::updateProperty(propertyName, value);
    if(tr("线颜色") == propertyName)
    {
        if(value.value<QColor>() != m_pen.color())
        {
            m_pen.setColor(value.value<QColor>());
            update();
        }
    }
}

void PointsItem::slot_updateGeometry()
{
    update();
}
