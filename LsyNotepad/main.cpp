#include "rhznotepad.h"
//#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    //���һ������
    QPixmap pixmap(":/Screen.bmp");
    QSplashScreen splash(pixmap);
    splash.show();

    RHZNotepad w;
    w.show();
    splash.finish(&w);

    return a.exec();
}
