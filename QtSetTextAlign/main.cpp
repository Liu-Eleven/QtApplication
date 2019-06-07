#include "textalign.h"
#include <QtTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QPixmap pixmap(":/Screen.png");
    QSplashScreen splash(pixmap);
    splash.show();
    //a.processEvents();

    TextAlign w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
