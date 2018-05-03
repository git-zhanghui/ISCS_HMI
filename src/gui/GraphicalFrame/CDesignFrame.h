#ifndef CDESIGNFRAME_H
#define CDESIGNFRAME_H

#include <QMainWindow>
#include "UIActions.h"
#include "PropertyBrowser.h"

namespace Ui {
class CDesignFrame;
}

class QDockWidget;
class CGraphicsScene;
class CGraphicsView;
class CGraphicsWnd;
class CToolList;

class CDesignFrame : public QMainWindow
{
    Q_OBJECT
public:
    enum E_Design_Mode
    {
        GraphicalShapeDesign = 0,
        GraphicalMapDesign = 1
    };

    explicit CDesignFrame(QWidget *parent = 0);
    ~CDesignFrame();

    void initialize();

protected:
    void initUI();
    void initGraphicalShapeDesign();
    void initGraphicalDiagramDesign();
    void initAction();
    void initDock();

protected slots:
    void slot_initProperties();
    void slot_updateProperties(QString propertyName, QVariant val);
    void slot_updateTips(const QString &content);
    void slot_updateSceneOrthogonal(bool checked);

private:
    UIActions * m_pActions;
    QToolBar * m_pFileToolBar;
    QToolBar * m_pIconToolBar;
    QToolBar * m_pEditToolBar;

    QDockWidget * m_pGraphicsShapeDockWidget;
    QDockWidget * m_pGraphicsLayoutDockWidget;
    QDockWidget * m_pGraphicsPropertyDockWidget;

    CToolList * m_pShapeTreeWidget;
    QWidget * m_pGraphicsLayoutWidget;
    PropertyBrowser *  m_propertyBrowser;
    CGraphicsScene * m_pGraphicsScene;
    CGraphicsView * m_pGraphicsView;

    Ui::CDesignFrame *ui;
};

#endif // CDESIGNFRAME_H
