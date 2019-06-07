#include "pictrans.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    PicTrans w;
    w.show();

    return a.exec();
}
