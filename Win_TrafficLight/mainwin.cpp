#include "mainwin.h"

MainWin::MainWin(QWidget *parent) :
    QFrame(parent)
{
    setWindowTitle(tr("红绿灯"));
    QFont font("ZYSong18030",12);
    setFont(font);

    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QHBoxLayout *hbMain = new QHBoxLayout(this) ;
    leftWin = new RGBLight(this);
    rightwindow = new RightWin(this);
    //开始状态机
    connect(rightwindow,SIGNAL(startStateMachine(int,int,int,int ,int ,int,int)),
            leftWin,SLOT(slotStartMachine(int,int,int,int ,int ,int,int)));
    //停止状态机
    connect(rightwindow ,SIGNAL(stopStateMachine()) ,
            leftWin, SLOT(slotStopMachine()));
    /*//LCD显示器*/
    connect(leftWin,SIGNAL(sendLcdNumber(int)),leftWin,SLOT(LcdDisplayNumber(int)));

    hbMain->setMargin(2);
    //设置该框架总的几份
    hbMain->setSpacing(7);
    hbMain->addWidget(leftWin);
    hbMain->addWidget(rightwindow,0,Qt::AlignCenter);
    hbMain->setStretchFactor(leftWin,3);
    hbMain->setStretchFactor(rightwindow,4);
    //hbMain->addStretch();

    setLayout(hbMain);

    setMaximumSize(350,350);
    setMinimumSize(350,350);
}
