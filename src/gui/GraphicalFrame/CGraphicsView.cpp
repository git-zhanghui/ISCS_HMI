#include "CGraphicsView.h"
#include "CGraphicsScene.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QGraphicsItem>
#include <QDebug>

#define ViewScaleRate (0.05)

CGraphicsView::CGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor( QGraphicsView::AnchorUnderMouse );
    setRubberBandSelectionMode(Qt::ContainsItemShape);
    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setAcceptDrops(true);
    if(dynamic_cast<CGraphicsScene*>(scene))
    {
        m_pScene = dynamic_cast<CGraphicsScene*>(scene);
        setScene(m_pScene);
    }
}

void CGraphicsView::zoomIn()
{
    scale((1 + ViewScaleRate), (1 + ViewScaleRate));
}

void CGraphicsView::zoomOut()
{
    scale(1 / (1 + ViewScaleRate), 1 / (1 + ViewScaleRate));
}

void CGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::gray);
    painter->drawRect(rect);
    painter->restore();
    QGraphicsView::drawBackground(painter, rect);
}

void CGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QPointF pf = mapToScene(event->pos());
    QString posTips;
    if(sceneRect().contains(pf))
    {
        posTips = QString("Position: %1, %2").arg(pf.toPoint().x()).arg(pf.toPoint().y());
    }
    else
    {
        posTips = tr("Ready");
    }
    emit sig_scenePressed(posTips);
    QGraphicsView::mousePressEvent(event);
}

void CGraphicsView::wheelEvent(QWheelEvent *event)
{
    static int nScale = 0;
    if(event->delta() > 0 && nScale <= 25)
    {
        nScale++;
        this->zoomIn();
    }
    else if(event->delta() < 0 && nScale >= -25)
    {
        if(nScale <= 0)
        {
            return;
        }
        nScale--;
        this->zoomOut();
    }
    QGraphicsView::wheelEvent(event);
}

void CGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    if(sceneRect().contains(event->pos()) && event->mimeData()->hasFormat("shape/id"))
    {
        event->acceptProposedAction();
    }

    QGraphicsView::dragEnterEvent(event);
}

void CGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    if(sceneRect().contains(mapToScene(event->pos())) && event->mimeData()->hasFormat("shape/id"))
    {
        event->acceptProposedAction();
    }
}
