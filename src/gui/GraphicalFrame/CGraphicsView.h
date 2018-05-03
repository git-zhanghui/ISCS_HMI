#ifndef CGRAPHICSVIEW_H
#define CGRAPHICSVIEW_H

#include <QGraphicsView>

class CGraphicsScene;

class CGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    CGraphicsView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);

public slots:
     void zoomIn();
     void zoomOut();

signals:
     void sig_scenePressed(const QString &);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

private:
    CGraphicsScene * m_pScene;
};

#endif // CGRAPHICSVIEW_H
