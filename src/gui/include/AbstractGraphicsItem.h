#ifndef ABSTRACTGRAPHICSITEM_H
#define ABSTRACTGRAPHICSITEM_H

#include "Export.h"
#include <QObject>
#include <QPen>
#include <QGraphicsItem>
#include "PropertyBrowser.h"

#define OUTLINEMARGINS (2)    //轮廓边距
#define INVALID_VALUE     (-1)  //无效值

class EXPORT AbstractGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY positionChanged FINAL)
    Q_PROPERTY(QSizeF size READ size WRITE resize NOTIFY geometryChanged)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity FINAL)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
    enum E_ITEM_TYPE
    {
        E_Graphics_Item = UserType + 100,
    };

    AbstractGraphicsItem(QGraphicsItem *parent = Q_NULLPTR);
    virtual ~AbstractGraphicsItem();

    QString shapeName();

    void setPos(const QPointF &position);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    virtual int type() const;

    virtual void properties(QList<PropertyType> &properties);
    virtual void updateProperty(QString propertyName, QVariant value);

    void setWidth(const qreal &w);
    void setHeight(const qreal &h);
    void resize(const QSizeF &sizeF);
    qreal width() const;
    qreal height() const;
    QSizeF size() const;
    QRectF rect() const;

Q_SIGNALS:
    void positionChanged();
    void geometryChanged();

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

protected:
    QString m_shapeName;
    qreal m_width;
    qreal m_height;
};


#endif // ABSTRACTGRAPHICSITEM_H
