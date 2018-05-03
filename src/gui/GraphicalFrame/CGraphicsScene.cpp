#include "CGraphicsScene.h"
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QPainter>
#include "GraphicsFactory.h"
#include <QDebug>
#include <QSpinBox>
#include <QGraphicsProxyWidget>
#include <QColorDialog>
#include "WidgetItem.h"

CGraphicsScene::CGraphicsScene(QObject *parent)
    : QGraphicsScene(parent),
      m_currentEditingItem(Q_NULLPTR),
      m_bOrthogonal(false)
{
    connect(this, SIGNAL(sceneRectChanged(QRectF)), this, SLOT(slot_updateOrthogonalPoints(QRectF)));
}

QPolygonF CGraphicsScene::orthogonalPoints() const
{
    return m_orthogonalPoints;
}

bool CGraphicsScene::orthogonal() const
{
    return m_bOrthogonal;
}

void CGraphicsScene::setOrthogonal(const bool &orthogonal)
{
    m_bOrthogonal = orthogonal;
    slot_updateOrthogonalPoints(sceneRect());
}

void CGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent)
{
    QGraphicsScene::contextMenuEvent(contextMenuEvent);
}

void CGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
    painter->save();
    QPen pen;
    pen.setWidthF(0);
    painter->setPen(pen);
    painter->setBrush(Qt::white);
    painter->drawRect(sceneRect().adjusted(-1, -1, 1, 1));
    if(m_bOrthogonal)
    {
        painter->setBrush(Qt::NoBrush);
        painter->drawPoints(m_orthogonalPoints);
    }
    painter->restore();
}

void CGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(m_bOrthogonal)
    {
        QPointF pos = event->scenePos();
        int x = (int)(pos.x() / 10);
        int y = (int)(pos.y() / 10);
        pos = QPointF(x * 10.0, y * 10.0);
        event->setScenePos(pos);
    }
    if(sceneRect().contains(event->scenePos()) && event->mimeData()->hasFormat("shape/id"))
    {
        GraphicsFactory * factory = GraphicsFactory::instance();
        AbstractGraphicsItem * item = factory->build(event->mimeData()->data("shape/id").toInt());
        clearSelection();
        if(item)
        {
            addItem(item);
            connect(item, SIGNAL(positionChanged()), this, SLOT(slot_itemPositionChanged()));
            item->setPos(event->scenePos());
            item->setSelected(true);
            if(qobject_cast<PointsItem*>(item))
            {
               PointsItem * pointItem = qobject_cast<PointsItem*>(item);
               pointItem->setEditStart();
            }
            if(qobject_cast<WidgetItem*>(item))
            {
               WidgetItem * widgetItem = qobject_cast<WidgetItem*>(item);
               widgetItem->setWidgetParent(views().front()->viewport());
            }
            m_currentEditingItem = item;
        }
        update();
    }
    QGraphicsScene::dropEvent(event);
}

void CGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(m_bOrthogonal)
    {
        updateMouseEvent(mouseEvent);
    }
    if(m_currentEditingItem)
    {
        PointsItem * item = qobject_cast<PointsItem*>(m_currentEditingItem);
        if(item && !item->isEditComplete())
        {
            item->setTipPoint(mouseEvent->scenePos() - item->pos());
        }
    }
    update();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void CGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(m_bOrthogonal)
    {
        updateMouseEvent(mouseEvent);
    }
    if(m_currentEditingItem)
    {
        PointsItem * item = qobject_cast<PointsItem*>(m_currentEditingItem);
        if(item && !item->isEditComplete())
        {
            if(Qt::LeftButton == mouseEvent->button())
            {
                item->appendPoint(mouseEvent->scenePos() - item->pos());
                if(dynamic_cast<LineItem*>(item))
                {
                    item->setEditComplete();
                    m_currentEditingItem = Q_NULLPTR;
                }
            }
            else if(Qt::RightButton == mouseEvent->button())
            {
                if(item->points().count() <= 1)
                {
                    removeItem(item);
                    delete item;
                    m_currentEditingItem = Q_NULLPTR;
                }
                else
                {
                    item->setEditComplete();
                    m_currentEditingItem = Q_NULLPTR;
                }
            }
        }
    }
    update();
    return QGraphicsScene::mousePressEvent(mouseEvent);
}

void CGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(m_bOrthogonal)
    {
        updateMouseEvent(mouseEvent);
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void CGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    QGraphicsScene::wheelEvent(wheelEvent);
}

void CGraphicsScene::updateMouseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(m_bOrthogonal)
    {
        QPointF pos = mouseEvent->scenePos();
        int x = (int)(pos.x() / 10);
        int y = (int)(pos.y() / 10);
        pos = QPointF(x * 10.0, y * 10.0);
        mouseEvent->setScenePos(pos);
    }
}

void CGraphicsScene::slot_updateOrthogonalPoints(const QRectF &rect)
{
    for(int nRow(0); nRow <= rect.height(); nRow += 10)
    {
        for(int nColum(0); nColum <= rect.width(); nColum += 10)
        {
            m_orthogonalPoints.append(QPointF(nColum, nRow));
        }
    }
    foreach(QGraphicsView * view, views())
    {
        view->resetCachedContent();
        view->viewport()->update();
    }
}

void CGraphicsScene::slot_itemPositionChanged()
{
    AbstractGraphicsItem * item = dynamic_cast<AbstractGraphicsItem*>(sender());
    if(item)
    {
        if(m_bOrthogonal)
        {
            QPointF pos = item->pos();
            int x = (int)(pos.x() / 10);
            int y = (int)(pos.y() / 10);
            pos = QPointF(x * 10.0, y * 10.0);
            if(item->pos() != pos)
            {
                item->setPos(pos);
            }
        }
    }
}


