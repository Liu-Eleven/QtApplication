#include "ToolBar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    ToolBar w;
    w.show();

    return a.exec();
}
