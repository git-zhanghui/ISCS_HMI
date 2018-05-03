#include "AbstractRegularItem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>

AbstractRegularItem::AbstractRegularItem(QGraphicsItem *parent)
    : AbstractGraphicsItem(parent),
      m_hoverPointIndex(INVALID_VALUE)
{
    m_brush = QBrush(Qt::white);
    connect(this, SIGNAL(geometryChanged()), this, SLOT(slot_updateGeometry()));
}

AbstractRegularItem::~AbstractRegularItem()
{

}

QRectF AbstractRegularItem::boundingRect() const
{
    qreal delta = m_pen.widthF() / 2.0 + OUTLINEMARGINS * 3 * 2;
    return QRectF(QPointF(), size()).adjusted(-delta, -delta, delta, delta);
}

QPainterPath AbstractRegularItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void AbstractRegularItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isSelected())
    {
        drawControlRect(painter);
    }
    AbstractGraphicsItem::paint(painter, option, widget);
}

void AbstractRegularItem::properties(QList<PropertyType> &properties)
{
    AbstractGraphicsItem::properties(properties);
    properties.append(qMakePair(QSizeF(m_width, m_height), tr("宽高")));
}

void AbstractRegularItem::updateProperty(QString propertyName, QVariant value)
{
    AbstractGraphicsItem::updateProperty(propertyName, value);
    if(tr("宽高") == propertyName)
    {
        if(value.toSizeF() != size())
        {
            m_previousWidth = m_width;
            m_previousHeight = m_height;
            m_previousPath = m_path;
            resize(value.toSizeF());
        }
    }
}

void AbstractRegularItem::drawControlRect(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(QColor(0, 0, 180, 100), 0.0, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRectF(0.0, 0.0, m_width, m_height));
    painter->restore();

    //draw out controlPoint
    painter->save();
    painter->setPen(QPen(Qt::black, 0.0, Qt::SolidLine));
    QMatrix matrix(painter->matrix());
    qreal scaleXFactor = 1.0 / matrix.m11();
    qreal scaleYFactor = 1.0 / matrix.m22();
    matrix.scale(scaleXFactor, scaleYFactor);
    painter->setMatrix(matrix);
    qreal length = OUTLINEMARGINS * 3;
    for(int nIndex(0); nIndex < m_controlRect.count(); nIndex++)
    {
        QPointF pf = m_controlRect[nIndex].center();
        pf = QPointF(pf.x() / scaleXFactor, pf.y() / scaleYFactor);
        QRectF rf = QRectF(QPointF(pf.x() - (length / 2), pf.y() - (length / 2)), QSize(length, length));
        painter->setBrush(Qt::lightGray);
        if(m_hoverPointIndex == nIndex)
        {
            painter->setBrush(Qt::red);
        }
        painter->drawRect(rf);
    }
    painter->restore();
}

void AbstractRegularItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_hoverPointIndex != INVALID_VALUE)
    {
        updateShapeGrometry(event->scenePos());
    }
    else
    {
        AbstractGraphicsItem::mouseMoveEvent(event);
    }
    update();
}

void AbstractRegularItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_previousWidth = m_width;
    m_previousHeight = m_height;
    m_previousPath = m_path;
    AbstractGraphicsItem::mousePressEvent(event);
}

void AbstractRegularItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    AbstractGraphicsItem::mouseReleaseEvent(event);
}

void AbstractRegularItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(!isSelected())
    {
        return;
    }
    AbstractGraphicsItem::hoverEnterEvent(event);
}

void AbstractRegularItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(!isSelected())
    {
        return;
    }
    m_hoverPointIndex = INVALID_VALUE;
    setCursor(Qt::ArrowCursor);
    AbstractGraphicsItem::hoverLeaveEvent(event);
    update();
}

void AbstractRegularItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(!isSelected())
    {
        return;
    }
    m_hoverPointIndex = INVALID_VALUE;
    setCursor(Qt::SizeAllCursor);
    for(int nIndex(0); nIndex < m_controlRect.count(); nIndex++)
    {
        if(m_controlRect.at(nIndex).contains(event->pos()))
        {
            m_hoverPointIndex = nIndex;
        }
    }
    if(m_hoverPointIndex != INVALID_VALUE)
    {
        switch (m_hoverPointIndex)
        {
        case 0:
        case 4:
            setCursor(Qt::SizeFDiagCursor);
            break;
        case 1:
        case 5:
            setCursor(Qt::SizeVerCursor);
            break;
        case 2:
        case 6:
            setCursor(Qt::SizeBDiagCursor);
            break;
        case 3:
        case 7:
            setCursor(Qt::SizeHorCursor);
            break;
        default:
            break;
        }
    }
    AbstractGraphicsItem::hoverMoveEvent(event);
    update();
}

void AbstractRegularItem::updateShapeGrometry(QPointF scenePos)
{
    qreal margins = OUTLINEMARGINS * 6;
    switch (m_hoverPointIndex)
    {
    case 0:
    {
        QPointF bottomRight = QPointF(pos().x() + m_width, pos().y() + m_height);
        if(scenePos.x() <= 0)
        {
            scenePos.setX(0);
        }
        else if(scenePos.x() >= bottomRight.x() - margins)
        {
            scenePos.setX(bottomRight.x() - margins);
        }

        if(scenePos.y() <= 0)
        {
            scenePos.setY(0);
        }
        else if(scenePos.y() >= bottomRight.y() - margins)
        {
            scenePos.setY(bottomRight.y() - margins);
        }
        setWidth(bottomRight.x() - scenePos.x());
        setHeight(bottomRight.y() - scenePos.y());
        setPos(scenePos);
        break;
    }
    case 1:
    {
        qreal left = pos().x();
        qreal bottom = pos().y() + m_height;
        if(scenePos.y() <= 0)
        {
            scenePos.setY(0);
        }
        else if(scenePos.y() >= bottom - margins)
        {
            scenePos.setY(bottom - margins);
        }
        setHeight(bottom - scenePos.y());
        setPos(QPointF(left, scenePos.y()));
        break;
    }
    case 2:
    {
        qreal left = pos().x();
        qreal bottom = pos().y() + m_height;
        if(scenePos.x() <= left + margins)
        {
            scenePos.setX(left + margins);
        }
        else if(scenePos.x() >= scene()->sceneRect().width())
        {
            scenePos.setX(scene()->sceneRect().width());
        }

        if(scenePos.y() <= 0)
        {
            scenePos.setY(0);
        }
        else if(scenePos.y() >= bottom - margins)
        {
            scenePos.setY(bottom - margins);
        }
        setWidth(scenePos.x() - left);
        setHeight(bottom - scenePos.y());
        setPos(QPointF(left, scenePos.y()));
        break;
    }
    case 3:
    {
        qreal width = scenePos.x() - pos().x();
        if(width <= margins)
        {
            width = margins;
        }
        if(scenePos.x() >= scene()->sceneRect().width())
        {
            width = scene()->sceneRect().width() - pos().x();
        }
        setWidth(width);
        break;
    }
    case 4:
    {
        qreal width = scenePos.x() - pos().x();
        qreal height = scenePos.y() - pos().y();
        if(width <= margins)
        {
            width = margins;
        }
        if(height <= margins)
        {
            height = margins;
        }
        if(scenePos.x() >= scene()->sceneRect().width())
        {
            width = scene()->sceneRect().width() - pos().x();
        }
        if(scenePos.y() >= scene()->sceneRect().height())
        {
            height = scene()->sceneRect().height() - pos().y();
        }
        resize(QSizeF(width, height));
        break;
    }
    case 5:
    {
        qreal height = scenePos.y() - pos().y();
        if(height <= margins)
        {
            height = margins;
        }
        if(scenePos.y() >= scene()->sceneRect().height())
        {
            height = scene()->sceneRect().height() - pos().y();
        }
        setHeight(height);
        break;
    }
    case 6:
    {
        QPointF topRight = QPointF(pos().x() + m_width, pos().y());
        if(scenePos.x() <= 0)
        {
            scenePos.setX(0);
        }
        else if(scenePos.x() >= topRight.x() - margins)
        {
            scenePos.setX(topRight.x() - margins);
        }

        if(scenePos.y() >= scene()->sceneRect().height())
        {
            scenePos.setY(scene()->sceneRect().height());
        }
        else if(scenePos.y() <= topRight.y() + margins)
        {
            scenePos.setY(topRight.y() + margins);
        }
        setWidth(topRight.x() - scenePos.x());
        setHeight(scenePos.y() - topRight.y());
        setPos(QPointF(scenePos.x(), topRight.y()));
        break;
    }
    case 7:
    {
        qreal right = pos().x() + m_width;
        if(scenePos.x() <= 0)
        {
            scenePos.setX(0);
        }
        if(scenePos.x() >= right - margins)
        {
            scenePos.setX(right - margins);
        }
        setWidth(right - scenePos.x());
        setPos(QPointF(scenePos.x(), pos().y()));
        break;
    }
    default:
        break;
    }
}

void AbstractRegularItem::updateControlRect()
{
    m_controlRect.clear();
    qreal length = OUTLINEMARGINS * 3;
    m_controlRect.append(QRectF(QPointF(-(length / 2), -(length / 2)), QSize(length, length)));
    m_controlRect.append(QRectF(QPointF(m_width / 2 - (length / 2), 0 - (length / 2)), QSize(length, length)));
    m_controlRect.append(QRectF(QPointF(m_width - (length / 2), -(length / 2)), QSize(length, length)));
    m_controlRect.append(QRectF(QPointF(m_width - (length / 2), m_height / 2 - (length / 2)), QSize(length, length)));
    m_controlRect.append(QRectF(QPointF(m_width - (length / 2), m_height - (length / 2)), QSize(length, length)));
    m_controlRect.append(QRectF(QPointF(m_width / 2 - (length / 2), m_height - (length / 2)), QSize(length, length)));
    m_controlRect.append(QRectF(QPointF(-(length / 2), m_height - (length / 2)), QSize(length, length)));
    m_controlRect.append(QRectF(QPointF(-(length / 2), m_height / 2 - (length / 2)), QSize(length, length)));
}

void AbstractRegularItem::updatePainterPath()
{
    if(m_previousPath.isEmpty() || m_path.isEmpty())
    {
        return;
    }
    qreal horFactor = m_width / m_previousWidth;
    qreal verFactor = m_height / m_previousHeight;
    for(int nIndex(0); nIndex < m_path.elementCount(); nIndex++)
    {
        m_path.setElementPositionAt(nIndex, m_previousPath.elementAt(nIndex).x * horFactor, m_previousPath.elementAt(nIndex).y * verFactor);
    }
}

void AbstractRegularItem::slot_updateGeometry()
{
    updatePainterPath();
    updateControlRect();
    update();
}
