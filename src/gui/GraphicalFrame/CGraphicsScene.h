#ifndef CGRAPHICSSCENE_H
#define CGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QApplication>
#include <QDesktopWidget>

#define MaxWidth (QApplication::desktop()->availableGeometry().width())
#define MaxHeight (QApplication::desktop()->availableGeometry().height())

class AbstractGraphicsItem;
class CGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CGraphicsScene(QObject *parent = Q_NULLPTR);

    //正交点集合
    QPolygonF orthogonalPoints() const;

    bool orthogonal() const;
    void setOrthogonal(const bool &orthogonal);

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *contextMenuEvent);
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent);

    void updateMouseEvent(QGraphicsSceneMouseEvent *mouseEvent);

Q_SIGNALS:
    void itemPropertyChanged();

private slots:
    void slot_updateOrthogonalPoints(const QRectF &rect);
    void slot_itemPositionChanged();

private:
    AbstractGraphicsItem * m_currentEditingItem;
    bool m_bOrthogonal;
    QPolygonF m_orthogonalPoints;
};

#endif // CGRAPHICSSCENE_H
