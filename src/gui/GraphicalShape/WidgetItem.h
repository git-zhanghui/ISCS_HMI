#ifndef WIDGETITEM_H
#define WIDGETITEM_H

#include "AbstractRegularItem.h"

class QWidget;

class EXPORT WidgetItem : public AbstractRegularItem
{
    Q_OBJECT
public:
    WidgetItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~WidgetItem();

    void setWidgetParent(QWidget * parent);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

private:
    QWidget * m_pWidget;
};

#endif // WIDGETITEM_H
