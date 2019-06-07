#include "driftbottle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());


    DriftBottle w;
    w.show();

    return a.exec();
}
