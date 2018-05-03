#ifndef UIACTION_H
#define UIACTION_H

class QAction;

class UIActions {
    friend class CDesignFrame;

private:
    QAction * newIcon;
    QAction * editIcon;
    QAction * saveIcon;
    QAction * closeIcon;

    QAction * newFile;
    QAction * editFile;
    QAction * saveFile;
    QAction * closeFile;

    QAction * copy;
    QAction * cut;
    QAction * paste;

    QAction * undo;
    QAction * redo;
};

#endif // UIACTION_H
