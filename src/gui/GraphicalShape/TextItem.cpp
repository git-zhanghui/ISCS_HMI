#include "TextItem.h"
#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsScene>

TextItem::TextItem(QGraphicsItem *parent)
    : AbstractGraphicsItem(parent)
{
    m_shapeName = tr("折线");
    m_contentText = tr("Text");
}

TextItem::~TextItem()
{

}

QRectF TextItem::boundingRect() const
{
      QFontMetrics fontMetrics(m_font);
      int pixelsWide = fontMetrics.width(m_contentText);
      int pixelsHigh = fontMetrics.height();
      return QRectF(0.0, 0.0, pixelsWide, pixelsHigh);
}

QPainterPath TextItem::shape() const
{
    QFontMetrics fontMetrics(m_font);
    int pixelsWide = fontMetrics.width(m_contentText);
    int pixelsHigh = fontMetrics.height();
    QRectF rf = QRectF(0.0, 0.0, pixelsWide, pixelsHigh);
    QPainterPath path;
    path.addRect(rf);
    return path;
}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    QFontMetrics fontMetrics(m_font);
    int pixelsWide = fontMetrics.width(m_contentText);
    int pixelsHigh = fontMetrics.height();
    QRectF rf = QRectF(0.0, 0.0, pixelsWide, pixelsHigh);
    painter->setPen(m_pen);
    painter->setFont(m_font);
    painter->drawText(rf, m_contentText);
    painter->restore();
    AbstractGraphicsItem::paint(painter, option, widget);
}

void TextItem::properties(QList<PropertyType> &properties)
{
    AbstractGraphicsItem::properties(properties);
    properties.append(qMakePair(m_contentText, tr("文本内容")));
    properties.append(qMakePair(m_pen.color(), tr("文字颜色")));
    properties.append(qMakePair(m_font, tr("字体")));
}

void TextItem::updateProperty(QString propertyName, QVariant value)
{
    AbstractGraphicsItem::updateProperty(propertyName, value);
    if(tr("文本内容") == propertyName)
    {
        if(value.toString() != m_contentText)
        {
            m_contentText = value.toString();
            scene()->update();
        }
    }
    else if(tr("文字颜色") == propertyName)
    {
        if(value.value<QColor>() != m_pen.color())
        {
            m_pen.setColor(value.value<QColor>());
            update();
        }
    }
    else if(tr("字体") == propertyName)
    {
        if(value.value<QFont>() != m_font)
        {
            m_font = value.value<QFont>();
            scene()->update();
        }
    }
}
