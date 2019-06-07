#include "rightwin.h"

RightWin::RightWin(QWidget *parent) :
    QWidget(parent)
{


    QLabel *Title = new QLabel(tr("MYlight"));
    QFont font("Times", 31, QFont::Bold);
    Title->setFont(font);
    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::red);
    Title->setPalette(pal);

    QLabel *label1_0 = new QLabel(tr("ºìµÆ£º"));
    RedState = new QSpinBox(this) ;
    RedState->setMinimum(2);
    RedState->setMaximum(11);
    QLabel *label1_1 = new QLabel(tr(" S"));

    QLabel *label1_2 = new QLabel(tr("ÉÁË¸£º"));
    RedCoru = new QSpinBox(this);
    RedCoru->setMinimum(3);
    RedCoru->setMaximum(6);
    QLabel *label1_3 = new QLabel(tr(" ´Î"));



    QLabel *label2_0 = new QLabel(tr("»ÆµÆ£º"));
    YellowState = new QSpinBox(this) ;
    YellowState->setMinimum(2);
    YellowState->setMaximum(11);
    QLabel *label2_1 = new QLabel(tr(" S"));

    QLabel *label2_2 = new QLabel(tr("ÉÁË¸£º"));
    YellowCoru = new QSpinBox(this);
    YellowCoru->setMinimum(3);
    YellowCoru->setMaximum(6);
    QLabel *label2_3 = new QLabel(tr(" ´Î"));

    QLabel *label3_0 = new QLabel(tr("»ÆµÆ£º"));
    GreenState = new QSpinBox(this) ;
    GreenState->setMinimum(2);
    GreenState->setMaximum(11);
    QLabel *label3_1 = new QLabel(tr(" S"));

    QLabel *label3_2 = new QLabel(tr("ÉÁË¸£º"));
    GreenCoru = new QSpinBox(this);
    GreenCoru->setMinimum(3);
    GreenCoru->setMaximum(6);
    QLabel *label3_3 = new QLabel(tr(" ´Î"));


    StartBtn = new QPushButton(tr("¿ªÊ¼"));
    connect(StartBtn,SIGNAL(clicked()),this,SLOT(startMachine()));
    StartBtn->setMaximumSize(61,31);

    StopBtn = new QPushButton(tr("Í£Ö¹"));
    connect(StopBtn,SIGNAL(clicked()),this,SLOT(stopMachine()));
    StopBtn->setMaximumSize(61,31);

    ResetBtn = new QPushButton(tr("ÖØÖÃ"));
    connect(ResetBtn,SIGNAL(clicked()),this,SLOT(ResetParameter()));
    ResetBtn->setMaximumSize(61,31);


    QGridLayout *GrLayout = new QGridLayout(this);
    GrLayout->addWidget(Title,0,0,1,3);
    GrLayout->addWidget(label1_0,1,0,1,1);
    GrLayout->addWidget(RedState, 1,1,1,1);
    GrLayout->addWidget(label1_1,1,2,1,1);

    GrLayout->addWidget(label1_2,2,0,1,1);
    GrLayout->addWidget(RedCoru,2,1,1,1);
    GrLayout->addWidget(label1_3,2,2,1,1);


    GrLayout->addWidget(label2_0,3,0,1,1);
    GrLayout->addWidget(YellowState,3,1,1,1);
    GrLayout->addWidget(label2_1,3,2,1,1);

    GrLayout->addWidget(label2_2,4,0,1,1);
    GrLayout->addWidget(YellowCoru,4,1,1,1);
    GrLayout->addWidget(label2_3,4,2,1,1);

    GrLayout->addWidget(label3_0,5,0,1,1);
    GrLayout->addWidget(GreenState,5,1,1,1);
    GrLayout->addWidget(label3_1,5,2,1,1);

    GrLayout->addWidget(label3_2,6,0,1,1);
    GrLayout->addWidget(GreenCoru,6,1,1,1);
    GrLayout->addWidget(label3_3,6,2,1,1);

    GrLayout->addWidget(StartBtn,7,0,1,1);
    GrLayout->addWidget(StopBtn,7,1,1,1);
    GrLayout->addWidget(ResetBtn,7,2,1,1);
    this->setLayout(GrLayout);

}
void RightWin::startMachine()
{
    qDebug()<<"RightWin --- >startMachine";
    //·¢ËÍÉÁË¸´ÎÊý
    int RedNum = RedCoru->value();
    int YelloNum = YellowCoru->value();
    int GreenNum = GreenCoru->value();

    //·¢ËÍÍ£ÖÍ×´Ì¬Ê±¼ä

    int keepRed = RedState->value();
    int keepYellow = YellowState->value();
    int keepGreen = GreenState->value();

    emit startStateMachine(RedNum , YelloNum , GreenNum,
                           keepRed , keepYellow, keepGreen, 1);
}
void RightWin::stopMachine()
{
    qDebug()<<"RightWin --- > stopMachine";
    emit stopStateMachine();
}

void RightWin::ResetParameter()
{
    //ÉÁË¸´ÎÊýÖØÖÃ
    RedCoru->setValue(3);
    YellowCoru->setValue(3);
    GreenCoru->setValue(3);
    //¸÷×´Ì¬Í£ÖÍÊ±¼äÖØÖÃ
    RedState->setValue(2);
    YellowState->setValue(2);
    GreenState->setValue(2);



    emit startStateMachine(3 , 3 , 3, 2, 2 ,2, 0);
}
