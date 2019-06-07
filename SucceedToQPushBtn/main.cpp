#include "winmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    WinMain w;
    w.show();

    return a.exec();
}
