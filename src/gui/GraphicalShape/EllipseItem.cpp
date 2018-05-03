#include "EllipseItem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

EllipseItem::EllipseItem(QGraphicsItem *parent)
    : AbstractRegularItem(parent)
{
    m_shapeName = tr("椭圆");
    m_width = 100.0;
    m_height = 100.0;
    m_path.addEllipse(0, 0, m_width, m_height);
    updateControlRect();
}

EllipseItem::~EllipseItem()
{

}

void EllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(m_path);
    painter->restore();
    AbstractRegularItem::paint(painter, option, widget);
}

void EllipseItem::properties(QList<PropertyType> &properties)
{
    AbstractRegularItem::properties(properties);
    properties.append(qMakePair(m_pen.color(), tr("轮廓颜色")));
    properties.append(qMakePair(m_brush.color(), tr("填充颜色")));
}

void EllipseItem::updateProperty(QString propertyName, QVariant value)
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
            m_brush.setColor(value.value<QColor>());
            update();
        }
    }
}

