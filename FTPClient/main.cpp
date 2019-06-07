#include "ftpclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    FTPClient *FtpC = new FTPClient;
    FtpC->show();

    return a.exec();
}
