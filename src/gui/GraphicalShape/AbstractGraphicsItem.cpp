#include "AbstractGraphicsItem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

AbstractGraphicsItem::AbstractGraphicsItem(QGraphicsItem *parent)
   : QGraphicsItem(parent),
     m_width(0.0),
     m_height(0.0)
{
    setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

AbstractGraphicsItem::~AbstractGraphicsItem()
{

}

QString AbstractGraphicsItem::shapeName()
{
    return m_shapeName;
}

void AbstractGraphicsItem::setPos(const QPointF &position)
{
    if(position != pos())
    {
        QGraphicsItem::setPos(position);
    }
}

QRectF AbstractGraphicsItem::boundingRect() const
{
    return QRectF();
}

QPainterPath AbstractGraphicsItem::shape() const
{
    return QPainterPath();
}

void AbstractGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


int AbstractGraphicsItem::type() const
{
    return E_Graphics_Item;
}

void AbstractGraphicsItem::properties(QList<PropertyType> &properties)
{
    properties.append(qMakePair(pos(), tr("位置")));
}

void AbstractGraphicsItem::updateProperty(QString propertyName, QVariant value)
{
    if(tr("位置") == propertyName)
    {
        if(value.toPointF() != pos())
        {
            prepareGeometryChange();
            setPos(value.toPointF());
        }
    }
}

void AbstractGraphicsItem::setWidth(const qreal &w)
{
    if(m_width != w)
    {
        prepareGeometryChange();
        m_width = w;
        emit geometryChanged();
    }
}

void AbstractGraphicsItem::setHeight(const qreal &h)
{
    if(m_height != h)
    {
        prepareGeometryChange();
        m_height = h;
        emit geometryChanged();
    }
}

void AbstractGraphicsItem::resize(const QSizeF &sizeF)
{
    if(size() != sizeF)
    {
        prepareGeometryChange();
        m_width =  sizeF.width();
        m_height = sizeF.height();
        emit geometryChanged();
    }
}

qreal AbstractGraphicsItem::width() const
{
    return m_width;
}

qreal AbstractGraphicsItem::height() const
{
    return m_height;
}

QSizeF AbstractGraphicsItem::size() const
{
    return QSizeF(m_width, m_height);
}

QRectF AbstractGraphicsItem::rect() const
{
    return QRectF(pos(), size());
}

void AbstractGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void AbstractGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void AbstractGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant AbstractGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
 {
    if(scene())
    {
        switch (change)
        {
            case ItemPositionChange:
                if(scene())
                {
                    QPointF position = value.toPointF();
                    QRectF rect = scene()->sceneRect().adjusted(0,0, -m_width, -m_height);
                    if (!rect.contains(position))
                    {
                        position.setX(qMin(rect.right(), qMax(position.x(), rect.left())));
                        position.setY(qMin(rect.bottom(), qMax(position.y(), rect.top())));
                        return position;
                    }
                    break;
                }
            case ItemPositionHasChanged:
                if(scene())
                {
                    emit positionChanged();
                    break;
                }
            default:
                break;
        }
    }
    return QGraphicsItem::itemChange(change, value);
 }
