#include "WidgetItem.h"
#include <QLabel>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>

WidgetItem::WidgetItem(QGraphicsItem *parent)
    : AbstractRegularItem(parent),
      m_pWidget(Q_NULLPTR)
{

}

WidgetItem::~WidgetItem()
{

}

void WidgetItem::setWidgetParent(QWidget *parent)
{
    m_pWidget = new QLabel(parent);
    dynamic_cast<QLabel*>(m_pWidget)->setText("HHHHHHHHHHHH");
    m_pWidget->show();
    QRectF widgetGeometry = m_pWidget->geometry();
    QPointF pf = scene()->views().front()->mapFromScene(pos());
//    QPointF pf = mapToScene(pos()) + scene()->;
    m_pWidget->setGeometry( pf.x(), pf.y(), widgetGeometry.width(), widgetGeometry.height());
}

QRectF WidgetItem::boundingRect() const
{
    return m_pWidget->rect().adjusted(-2,-2,2,2);
}

QPainterPath WidgetItem::shape() const
{
    QPainterPath path;
    path.addRect(m_pWidget->rect());
    return path;
}

void WidgetItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->save();
    painter->setBrush(Qt::red);
    painter->drawRect(m_pWidget->rect());
    painter->restore();
}
