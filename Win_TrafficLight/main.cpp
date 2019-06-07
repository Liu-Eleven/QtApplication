#include "mainwin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("Win_TrafficLight_ch");
    a.installTranslator(&translator);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    MainWin w;
    w.show();

    return a.exec();
}
