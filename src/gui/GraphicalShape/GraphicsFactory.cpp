#include "GraphicsFactory.h"
#include "WidgetItem.h"

GraphicsFactory *GraphicsFactory::instance()
{
    static GraphicsFactory factory;
    return &factory;
}

GraphicsFactory::GraphicsFactory()
{

}

AbstractGraphicsItem *GraphicsFactory::build(const int &id)
{
    switch (id) {
    case 10001:
        return new LineItem();
        break;
    case 10002:
        return new PolygonLineItem();
        break;
    case 10003:
        return new PolygonShapeItem();
        break;
    case 10004:
        return new RectangleItem();
        break;
    case 10005:
        return new EllipseItem();
        break;
    case 10006:
        return new TextItem();
        break;
    case 10007:
        return new ImageItem();
        break;
    case 10102:
        return new WidgetItem();
        break;
    default:
        return (AbstractGraphicsItem *)Q_NULLPTR;
        break;
    }
    return (AbstractGraphicsItem *)Q_NULLPTR;
}

