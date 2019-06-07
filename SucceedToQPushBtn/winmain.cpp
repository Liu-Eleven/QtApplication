#include "winmain.h"

WinMain::WinMain(QWidget *parent):QWidget(parent)
{
    qDebug()<<tr("只初始化一次");
    //加载一副图片
    QPixmap image(":/images/Main.bmp");
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(image)));
    setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *hblayout = new QHBoxLayout;

    mybtn = new SucceedTOQPB;
    strTip = "11";
    mybtn->SetTip(strTip);
    mybtn->setMinimumSize(151,47);

    hblayout->addStretch();
    hblayout->addWidget(mybtn);
    hblayout->addStretch();

    connect(mybtn,SIGNAL(pressed()),this,SLOT(slotClickMe()));

    layout->addStretch();
    layout->addStretch();
    layout->addLayout(hblayout);
    layout->addStretch();


    setLayout(layout);

    resize(image.width(),image.height());
}


void WinMain::slotClickMe()
{
   // QMessageBox::information(this,tr("提示"),tr("捞一捞"));
    int i_tip = strTip.toInt();
    qDebug()<<"i_tip = "<<i_tip;

    if(i_tip == 1)
    {
        mybtn->SetTip("");
        return ;

    }
    strTip = QString::number(--i_tip);
    qDebug()<<strTip;



    mybtn->SetTip(strTip);

}
