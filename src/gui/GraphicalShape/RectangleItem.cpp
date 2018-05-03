#include "RectangleItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

RectangleItem::RectangleItem(QGraphicsItem *parent)
    : AbstractRegularItem(parent)
{
    m_shapeName = tr("矩形");
    m_width = 100.0;
    m_height = 100.0;
    m_path.addRect(0, 0, m_width, m_height);
    updateControlRect();
}

RectangleItem::~RectangleItem()
{

}

void RectangleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(m_path);
    painter->restore();
    AbstractRegularItem::paint(painter, option, widget);
}

void RectangleItem::properties(QList<PropertyType> &properties)
{
    AbstractRegularItem::properties(properties);
    properties.append(qMakePair(m_pen.color(), tr("轮廓颜色")));
    properties.append(qMakePair(m_brush, tr("填充颜色")));
}

void RectangleItem::updateProperty(QString propertyName, QVariant value)
{
    AbstractRegularItem::updateProperty(propertyName, value);
    if(tr("轮廓颜色") == propertyName)
    {
        if(value.value<QColor>() != m_pen.color())
        {
            m_pen.setColor(value.value<QColor>());
            update();
        }
    }
    else if(tr("填充颜色") == propertyName)
    {
        if(value.value<QColor>() != m_brush.color())
        {
            m_brush = value.value<QBrush>();
            update();
        }
    }
}
