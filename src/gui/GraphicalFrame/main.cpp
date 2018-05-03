#include "CDesignFrame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CDesignFrame w;
    w.showMaximized();

    return a.exec();
}
