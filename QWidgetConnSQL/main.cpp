#include <QtGui/QApplication>
#include "misdemo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    MISDemo w;
    w.show();
    return a.exec();
}
