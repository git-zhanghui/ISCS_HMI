#include "BrushLabel.h"
#include <QPainter>

BrushLabel::BrushLabel(QWidget *parent, QBrush brush)
    : QLabel(parent),
      m_brush(brush)
{

}

QBrush BrushLabel::brush() const
{
    return m_brush;
}

void BrushLabel::setBrush(const QBrush &brush)
{
    if(m_brush != brush)
    {
        m_brush = brush;
    }
}

void BrushLabel::paintEvent(QPaintEvent *pEvent)
{
    Q_UNUSED(pEvent)
    QPainter painter(this);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
    painter.fillRect(rect().adjusted(2, 2, -2, -2), m_brush);
}

void BrushLabel::mousePressEvent(QMouseEvent *pEvent)
{
    QLabel::mousePressEvent(pEvent);
    emit pressed();
}
