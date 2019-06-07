#include "mainwin.h"

MainWin::MainWin(QWidget *parent) :
    QFrame(parent)
{
    setWindowTitle(tr("���̵�"));
    QFont font("ZYSong18030",12);
    setFont(font);

    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    QHBoxLayout *hbMain = new QHBoxLayout(this) ;
    leftWin = new RGBLight(this);
    rightwindow = new RightWin(this);
    //��ʼ״̬��
    connect(rightwindow,SIGNAL(startStateMachine(int,int,int,int ,int ,int,int)),
            leftWin,SLOT(slotStartMachine(int,int,int,int ,int ,int,int)));
    //ֹͣ״̬��
    connect(rightwindow ,SIGNAL(stopStateMachine()) ,
            leftWin, SLOT(slotStopMachine()));
    /*//LCD��ʾ��*/
    connect(leftWin,SIGNAL(sendLcdNumber(int)),leftWin,SLOT(LcdDisplayNumber(int)));

    hbMain->setMargin(2);
    //���øÿ���ܵļ���
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
