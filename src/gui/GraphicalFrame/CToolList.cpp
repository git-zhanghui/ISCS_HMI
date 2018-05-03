#include "CToolList.h"
#include <QFile>
#include <QMenu>
#include <QAction>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QDragEnterEvent>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QProcessEnvironment>

CShapeWidgetItem::CShapeWidgetItem(const QString &string, int type)
    : QTreeWidgetItem(QStringList() << string, type)
{

}

int CShapeWidgetItem::id() const
{
    return m_nId;
}

QString CShapeWidgetItem::iconName() const
{
    return m_strIconName;
}

void CShapeWidgetItem::setId(const int &id)
{
    m_nId = id;
}

void CShapeWidgetItem::setIconName(const QString &name)
{
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    if(environment.contains(QString("ISCS_HOME")))
    {
        QString strIconName = QString(environment.value(QString("ISCS_HOME")) + QString("\\image\\icon\\") + name);
        QIcon shapeIcon(strIconName);
        if(!strIconName.isEmpty())
        {
            setIcon(0, shapeIcon);
        }
    }
    m_strIconName = name;
}


/**********************************************************************************
 *                                                   图元工具箱                                                      *
 *********************************************************************************/

CToolList::CToolList(QWidget *parent)
    : QTreeWidget(parent)
{
    setAcceptDrops(true);
    setDragDropMode(DragDrop);
    header()->setVisible(false);
    initialize();
}

void CToolList::initialize()
{
    QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
    if(environment.contains(QString("ISCS_HOME")))
    {
        m_strConfigFileName = QString(environment.value(QString("ISCS_HOME")) + QString("\\config\\shapeList.json"));
        loadConfig();
    }
    else
    {
        qWarning("shapeList.json is not Exists!");
    }
}

void CToolList::loadConfig()
{
    qInfo("load shapeList.json");
    QFile jsonFile;
    jsonFile.setFileName(m_strConfigFileName);
    if(jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString data = jsonFile.readAll();
        QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
        QJsonArray jsonArray = document.array();
        if(!jsonArray.isEmpty())
        {
            for(int nGroupIndex(0); nGroupIndex < jsonArray.count(); nGroupIndex++)
            {
                if(jsonArray.at(nGroupIndex).isObject())
                {
                    QJsonObject group = jsonArray.at(nGroupIndex).toObject();
                    QJsonObject::const_iterator groupIterator = group.constBegin();
                    while(groupIterator != group.constEnd())
                    {
                        QString groupName = groupIterator.key();
                        appendShapeGroup(groupName);
                        if(groupIterator.value().isArray())
                        {
                            QJsonArray shapeArray = groupIterator.value().toArray();
                            for(int nIndex(0); nIndex < shapeArray.count(); nIndex++)
                            {
                                if(shapeArray.at(nIndex).isObject())
                                {
                                    QJsonObject shape = shapeArray.at(nIndex).toObject();
                                    QJsonObject::const_iterator shapeIterator = shape.constBegin();
                                    while(shapeIterator != shape.constEnd())
                                    {
                                        QString shapeName = shapeIterator.key();
                                        QJsonObject shapeProperty = shapeIterator.value().toObject();
                                        int shapeID = shapeProperty.value("id").toInt();
                                        QString shapeIcon = shapeProperty.value("icon").toString();
                                        m_shapes.insert(shapeName, shapeID);
                                        appendShape(shapeName, groupName, shapeID, shapeIcon);
                                        shapeIterator++;
                                    }
                                }
                            }
                        }
                        groupIterator++;
                    }
                }
            }
        }
    }
    else
    {
        qWarning("ToolList.json is failed to open!");
    }
    jsonFile.close();
}

void CToolList::saveConfig()
{
    qInfo("save ToolList.json");
    QFile jsonFile;
    jsonFile.setFileName(m_strConfigFileName);
    if(jsonFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument document;
        QJsonArray array;
        for(int nGroupIndex(0); nGroupIndex < topLevelItemCount(); nGroupIndex++)
        {
            QJsonObject group;
            QTreeWidgetItem * pTopLevelItem = topLevelItem(nGroupIndex);
            QString strGoupName = pTopLevelItem->text(0);
            QJsonArray shapeArray;
            for(int nShapeIndex(0); nShapeIndex < pTopLevelItem->childCount(); nShapeIndex++)
            {
                QTreeWidgetItem * pChildShapeItem = pTopLevelItem->child(nShapeIndex);
                if(dynamic_cast<CShapeWidgetItem*>(pChildShapeItem))
                {
                    CShapeWidgetItem * item = dynamic_cast<CShapeWidgetItem*>(pChildShapeItem);
                    QString shapeName = item->text(0);
                    int nId = item->id();
                    QString strIconName = item->iconName();
                    QJsonObject shape;
                    QJsonObject shapeProperty;
                    shapeProperty.insert(QString("id"), nId);
                    shapeProperty.insert(QString("icon"), strIconName);
                    shape.insert(shapeName, shapeProperty);
                    shapeArray.append(shape);
                }
            }
            group.insert(strGoupName, shapeArray);
            array.insert(nGroupIndex, group);
        }
        document.setArray(array);
        jsonFile.write(document.toJson());
    }
    jsonFile.close();
}

void CToolList::appendShapeGroup(const QString &groupName)
{
    addTopLevelItem(new QTreeWidgetItem(QStringList() << groupName));
}

void CToolList::removeShapeGroup(const QString &groupName)
{

}

void CToolList::appendShape(const QString &shapeName, const QString &groupName, const int &id, const QString &iconName)
{
    for(int nIndex(0); nIndex < topLevelItemCount(); nIndex++)
    {
        if(topLevelItem(nIndex)->text(0) == groupName)
        {
            CShapeWidgetItem * item = new CShapeWidgetItem(shapeName);
            item->setId(id);
            item->setIconName(iconName);
            topLevelItem(nIndex)->addChild(item);
        }
    }
}

void CToolList::removeShape(const QString &shapeName, const QString &groupName)
{

}

void CToolList::contextMenuEvent(QContextMenuEvent *event)
{
    event->accept();
    QMenu *contextMenu = new QMenu(this);
    QTreeWidgetItem * item = itemAt(mapFromGlobal(QCursor::pos()));
    if(!item)
    {
        QAction * addGroup = new QAction(tr("添加图形组"), this);
        connect(addGroup, SIGNAL(triggered()), this, SLOT(slot_appendGroup()));
        contextMenu->addAction(addGroup);
    }
    else if(item && dynamic_cast<CShapeWidgetItem*>(item))
    {
        QAction * removeShape = new QAction(tr("删除图形"), this);
        connect(removeShape, SIGNAL(triggered()), this, SLOT(slot_removeShape()));
        contextMenu->addAction(removeShape);
    }
    else if(item && !dynamic_cast<CShapeWidgetItem*>(item))
    {
        QAction * addShape = new QAction(tr("添加图形"), this);
        QAction * removeGroup = new QAction(tr("删除图形组"), this);
        connect(addShape, SIGNAL(triggered()), this, SLOT(slot_appendShape()));
        connect(removeGroup, SIGNAL(triggered()), this, SLOT(slot_removeGroup()));
        contextMenu->addAction(addShape);
        contextMenu->addAction(removeGroup);
    }
    contextMenu->exec(QCursor::pos());
}

void CToolList::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("shape/id"))
    {
        event->acceptProposedAction();
    }
}

void CToolList::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat("shape/id"))
    {
        event->acceptProposedAction();
    }
}

void CToolList::dropEvent(QDropEvent *event)
{
    if(event->source() == this)
    {
        event->ignore();
    }
}

void CToolList::startDrag(Qt::DropActions supportedActions)
{
    Q_UNUSED(supportedActions)
    QTreeWidgetItem * item = currentItem();
    if(item && dynamic_cast<CShapeWidgetItem*>(item))
    {
        CShapeWidgetItem * shapeWidgetItem = dynamic_cast<CShapeWidgetItem*>(item);
        QDrag * drag = new QDrag(this);
        QMimeData * mimeData = new QMimeData();
        mimeData->setData("shape/id", QString::number(shapeWidgetItem->id()).toUtf8());
        drag->setMimeData(mimeData);

        QString strPixmapName;
        QProcessEnvironment environment = QProcessEnvironment::systemEnvironment();
        if(environment.contains(QString("ISCS_HOME")))
        {
            strPixmapName = QString(environment.value(QString("ISCS_HOME")) + QString("\\image\\icon\\") + shapeWidgetItem->iconName());
        }

        QPixmap pixmap = item->icon(0).pixmap(24,24);
        drag->setPixmap(pixmap);
        QPoint hotSpot = drag->hotSpot() - QPoint(10, 0);
        drag->setHotSpot(hotSpot);
        drag->exec(Qt::CopyAction);
    }
}

void CToolList::slot_appendShape()
{

}

void CToolList::slot_removeShape()
{

}

void CToolList::slot_appendGroup()
{

}

void CToolList::slot_removeGroup()
{

}

