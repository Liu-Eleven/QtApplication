#include <QtGui/QApplication>
#include "misdemo.h"
#include "ConnectDB.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    if(!ConnectDB())
    {
        return -1;
    }
    MISDemo w;
    w.show();
    return a.exec();
}
