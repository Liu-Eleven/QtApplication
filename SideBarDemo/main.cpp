#include <QtGui/QApplication>
#include "sidebardemo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SideBarDemo w;
    w.show();

    return a.exec();
}
