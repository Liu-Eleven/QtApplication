#include <QtGui/QApplication>
#include "mywebkit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    MyWebKit w;
    w.show();

    return a.exec();
}
