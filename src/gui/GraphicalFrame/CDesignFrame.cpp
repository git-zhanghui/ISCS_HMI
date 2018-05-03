#include "CDesignFrame.h"
#include "ui_CDesignFrame.h"
#include <QToolBar>
#include <QToolButton>
#include <QDockWidget>
#include <QTreeWidget>
#include "CGraphicsScene.h"
#include "CGraphicsView.h"
#include "CToolList.h"
#include "AbstractGraphicsItem.h"

CDesignFrame::CDesignFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CDesignFrame)
{
    ui->setupUi(this);
    qInfo("initialize...");
    initialize();
}

CDesignFrame::~CDesignFrame()
{
    delete ui;
}

void CDesignFrame::initialize()
{
    initUI();
}

void CDesignFrame::initUI()
{
    initAction();
    initDock();
    initGraphicalShapeDesign();
    setCentralWidget(m_pGraphicsView);
    ui->statusBar->showMessage(tr("Ready"));
    QToolButton * orthogonalButton = new QToolButton(this);
    orthogonalButton->setText(tr("正交"));
    orthogonalButton->setCheckable(true);
    ui->statusBar->addPermanentWidget(orthogonalButton);
    connect(orthogonalButton, SIGNAL(toggled(bool)), this, SLOT(slot_updateSceneOrthogonal(bool)));

}

void CDesignFrame::initGraphicalShapeDesign()
{
    m_pGraphicsScene = new CGraphicsScene(this);
    m_pGraphicsView = new CGraphicsView(m_pGraphicsScene, this);
    m_pGraphicsView->setSceneRect(0, 0, MaxWidth/ 8.0, MaxHeight/ 4.0);
    m_pGraphicsScene->setSceneRect(0, 0, MaxWidth/ 8.0, MaxHeight/ 4.0);
    connect(m_pGraphicsScene, SIGNAL(selectionChanged()), this, SLOT(slot_initProperties()));
    connect(m_pGraphicsScene, SIGNAL(itemPropertyChanged()), this, SLOT(slot_initProperties()));
    connect(m_pGraphicsView, SIGNAL(sig_scenePressed(QString)), this, SLOT(slot_updateTips(QString)));
}

void CDesignFrame::initGraphicalDiagramDesign()
{

}

void CDesignFrame::initAction()
{
    m_pActions = new UIActions();
    m_pIconToolBar = new QToolBar(tr("图形工具"), this);
    m_pFileToolBar = new QToolBar(tr("图幅工具"), this);
    m_pEditToolBar = new QToolBar(tr("编辑工具"), this);

    m_pActions->newIcon = new QAction(tr("NewIcon"), this);
    m_pActions->editIcon = new QAction(tr("EditIcon"), this);
    m_pActions->saveIcon = new QAction(tr("SaveIcon"), this);
    m_pActions->closeIcon = new QAction(tr("CloseIcon"), this);

    m_pActions->newFile = new QAction(tr("NewFile"), this);
    m_pActions->editFile = new QAction(tr("EditFile"), this);
    m_pActions->saveFile = new QAction(tr("SaveFile"), this);
    m_pActions->closeFile = new QAction(tr("CloseFile"), this);

    m_pActions->copy = new QAction(tr("copy"), this);
    m_pActions->cut = new QAction(tr("cut"), this);
    m_pActions->paste = new QAction(tr("paste"), this);
    m_pActions->undo = new QAction(tr("undo"), this);
    m_pActions->redo = new QAction(tr("redo"), this);

    addToolBar(m_pIconToolBar);
    addToolBar(m_pFileToolBar);
    addToolBar(m_pEditToolBar);
    m_pIconToolBar->addActions(QList<QAction*>() << m_pActions->newIcon << m_pActions->editIcon << m_pActions->saveIcon << m_pActions->closeIcon);
    m_pFileToolBar->addActions(QList<QAction*>() << m_pActions->newFile << m_pActions->editFile << m_pActions->saveFile << m_pActions->closeFile);
    m_pEditToolBar->addActions(QList<QAction*>() << m_pActions->copy << m_pActions->cut << m_pActions->paste << m_pActions->undo << m_pActions->redo);
}

void CDesignFrame::initDock()
{
    m_pGraphicsShapeDockWidget = new QDockWidget(tr("工具箱"), this);
    m_pShapeTreeWidget = new CToolList(this);
    m_pGraphicsShapeDockWidget->setWidget(m_pShapeTreeWidget);
    m_pShapeTreeWidget->resize(MaxWidth / 5.0, m_pShapeTreeWidget->height());

    m_pGraphicsLayoutDockWidget = new QDockWidget(tr("图层"), this);
    m_pGraphicsLayoutWidget = new QTreeWidget(this);
    m_pGraphicsLayoutDockWidget->setWidget(m_pGraphicsLayoutWidget);
    m_pGraphicsLayoutWidget->resize(MaxWidth / 5.0, m_pShapeTreeWidget->height());

    m_pGraphicsPropertyDockWidget = new QDockWidget(tr("属性"), this);
    m_propertyBrowser = new PropertyBrowser(this);
    m_pGraphicsPropertyDockWidget->setWidget(m_propertyBrowser);
    m_propertyBrowser->resize(MaxWidth / 5.0, m_pShapeTreeWidget->height());
    connect(m_propertyBrowser, SIGNAL(propertyValueChanged(QString,QVariant)), this, SLOT(slot_updateProperties(QString,QVariant)));

    addDockWidget(Qt::LeftDockWidgetArea, m_pGraphicsShapeDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_pGraphicsLayoutDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_pGraphicsPropertyDockWidget);
}

void CDesignFrame::slot_initProperties()
{
    PropertyGroup  group;
    QList<PropertyGroup> property;
    if(!m_pGraphicsScene->selectedItems().isEmpty())
    {
        AbstractGraphicsItem * item = dynamic_cast<AbstractGraphicsItem*>(m_pGraphicsScene->selectedItems().first());
        if(item)
        {
            QList<PropertyType> properties;
            item->properties(properties);
            group.first = item->shapeName();
            group.second = properties;
        }
    }

    property.append(group);
    m_propertyBrowser->initProperties(property);
}

void CDesignFrame::slot_updateProperties(QString propertyName, QVariant val)
{
    if(!m_pGraphicsScene->selectedItems().isEmpty())
    {
        AbstractGraphicsItem * item = dynamic_cast<AbstractGraphicsItem*>(m_pGraphicsScene->selectedItems().first());
        if(item)
        {
            item->updateProperty(propertyName, val);
        }
    }
}

void CDesignFrame::slot_updateTips(const QString &content)
{
    ui->statusBar->showMessage(content);
}

void CDesignFrame::slot_updateSceneOrthogonal(bool checked)
{
    m_pGraphicsScene->setOrthogonal(checked);
}

