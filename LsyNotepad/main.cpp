#include "rhznotepad.h"
//#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    //添加一个屏风
    QPixmap pixmap(":/Screen.bmp");
    QSplashScreen splash(pixmap);
    splash.show();

    RHZNotepad w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
