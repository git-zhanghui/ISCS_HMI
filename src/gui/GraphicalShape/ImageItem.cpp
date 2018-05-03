#include "ImageItem.h"
#include <QPainter>

ImageItem::ImageItem(QGraphicsItem *parent)
    : AbstractRegularItem(parent)
{
    m_shapeName = tr("图片");
    m_width = 100.0;
    m_height = 100.0;
    updateControlRect();
    m_pen.setStyle(Qt::DashLine);
    m_pen.setWidthF(0.0);
}

ImageItem::~ImageItem()
{

}

void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    if(m_imagePath.isEmpty())
    {
        painter->fillRect(QRectF(QPointF(), size()), Qt::gray);
        painter->drawText(QRectF(QPointF(), size()), Qt::AlignHCenter | Qt::AlignVCenter, tr("未找到对象"));
    }
    painter->restore();
    AbstractRegularItem::paint(painter, option, widget);
}

void ImageItem::properties(QList<PropertyType> &properties)
{
    AbstractRegularItem::properties(properties);
    properties.append(qMakePair(m_imagePath, tr("图片路径")));
}

void ImageItem::updateProperty(QString propertyName, QVariant value)
{
    AbstractRegularItem::updateProperty(propertyName, value);
    if(tr("图片路径") == propertyName)
    {
        if(value.toString() != m_imagePath)
        {
            m_imagePath = value.toString();
            update();
        }
    }
}
