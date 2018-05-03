#ifndef CTOOLLIST_H
#define CTOOLLIST_H

#include <QTreeWidget>

class CShapeWidgetItem : public QTreeWidgetItem
{
public:
    explicit CShapeWidgetItem(const QString &string, int type = Type);

    int id() const;
    QString iconName() const;

    void setId(const int &id);
    void setIconName(const QString &name);

private:
    int m_nId;
    QString m_strIconName;
};

class CToolList : public QTreeWidget
{
    Q_OBJECT
public:
    CToolList(QWidget *parent = Q_NULLPTR);

    void initialize();

    void loadConfig();
    void saveConfig();

    void appendShapeGroup(const QString &groupName);
    void removeShapeGroup(const QString &groupName);

    void appendShape(const QString &shapeName, const QString &groupName, const int &id, const QString &iconName = QString());
    void removeShape(const QString &shapeName, const QString &groupName);

protected:
    void contextMenuEvent(QContextMenuEvent * event);

    void dragEnterEvent(QDragEnterEvent * event);
    void dragMoveEvent(QDragMoveEvent * event);
    void dropEvent(QDropEvent * event);
    void startDrag(Qt::DropActions supportedActions);

private slots:
    void slot_appendShape();
    void slot_removeShape();
    void slot_appendGroup();
    void slot_removeGroup();

private:
    QString m_strConfigFileName;
    QMap<QString, int> m_shapes;
};

#endif // CTOOLLIST_H
