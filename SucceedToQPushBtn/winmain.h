#ifndef WINMAIN_H
#define WINMAIN_H

#include <QtGui>
#include "STQPushBtn.h"

class WinMain:public QWidget
{
    Q_OBJECT
public:
    WinMain(QWidget *parent = 0);


private slots:
    void slotClickMe();

private:
    SucceedTOQPB *mybtn;

    QString strTip ;
};

#endif // WINMAIN_H
