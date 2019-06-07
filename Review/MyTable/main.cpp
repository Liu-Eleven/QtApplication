#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB18030"));


    MainWindow w;
    w.show();

    return a.exec();
}
