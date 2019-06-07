#include "leftwin.h"



RGBLight::RGBLight(QWidget *parent)
    : QWidget(parent)
{
    msec_Red = 1;
    msec_Yellow = 1;
    msec_Green = 1;

    msec_keepRed = 2;
    msec_keepYellow = 2;
    msec_keepGreen = 2;

    LcdTimer = new QTimer(this);
    LcdTimer->setInterval(1000);
    connect(LcdTimer,SIGNAL(timeout()) , this,SLOT(UpdateLcdNumber()));

    CreatLight();
}

RGBLight::~RGBLight()
{

}

void RGBLight::CreatLight()
{
    scene = new QGraphicsScene(this);
    //初始化镜头
    scene->setSceneRect(0,0,G_w,G_h*3);
    scene->setBackgroundBrush(Qt::black);



    //建立一个灯
    light = new MyLight;
    //初始化灯的位置
    light->setPos(50,50);
    //红色状态
    RedState = new QState;
    RedState->assignProperty(light,"color",Qt::red);
    RedState->assignProperty(light,"pos",QPoint(50,50));
    //红色闪烁状态
    QState *RedCoruscate = new QState;
    //红色闪烁状态子状态
    QState *Red_State = new QState(RedCoruscate) ;
    QState *RedCloseState = new QState(RedCoruscate);

    //红色状态各个位子
    Red_State->assignProperty(light,"color",Qt::red);
    Red_State->assignProperty(light,"pos",QPoint(50,50));
    RedCloseState->assignProperty(light,"color",Qt::black);
    RedCloseState->assignProperty(light,"pos",QPoint(50,50));
    //设置闪烁状态初始状态
    RedCoruscate->setInitialState(Red_State);
//end red light initializtion****************************************************************//

    //黄色状态
    YellowState = new QState;
    YellowState->assignProperty(light,"color",Qt::yellow);
    YellowState->assignProperty(light,"pos",QPoint(50,150));
    //黄色闪烁状态
    QState *YellowCoruscate = new QState;
    //黄色闪烁状态子状态
    QState *Yellow_State = new QState(YellowCoruscate) ;
    QState *YellowCloseState = new QState(YellowCoruscate);

    Yellow_State->assignProperty(light,"color",Qt::yellow);
    Yellow_State->assignProperty(light,"pos",QPoint(50,150));
    YellowCloseState->assignProperty(light,"color",Qt::black);
    YellowCloseState->assignProperty(light,"pos",QPoint(50,150));
    //设置黄色状态初始状态
    YellowCoruscate->setInitialState(Yellow_State);
// end yellow light initializtion**************************************************************//
    //绿色状态
    GreenState = new QState;
    GreenState->assignProperty(light,"color",Qt::green);
    GreenState->assignProperty(light,"pos",QPoint(50,250));
    //绿色闪烁状态
     QState *GreenCoruscate = new QState;
    //绿色闪烁状态子状态
     QState *Green_State = new QState(GreenCoruscate);
     QState *GreenCloseState = new QState(GreenCoruscate);

     Green_State->assignProperty(light,"color",Qt::green);
     Green_State->assignProperty(light,"pos",QPoint(50,250));
     GreenCloseState->assignProperty(light,"color",Qt::black);
     GreenCloseState->assignProperty(light,"pos",QPoint(50,250));
     //设定绿色闪烁状态初始状态
     GreenCoruscate->setInitialState(Green_State);
//end green light initializtion ***************************************************************//


     //红灯闪烁
     RL_Coruscate = new QTimer;
     RL_Coruscate->setSingleShot(true);
     RL_Coruscate->setInterval(521);

     connect(Red_State,SIGNAL(entered()), RL_Coruscate,SLOT(start()));
     Red_State->addTransition(RL_Coruscate,SIGNAL(timeout()),RedCloseState);

     connect(RedCloseState,SIGNAL(entered ()),RL_Coruscate,SLOT(start()));
     RedCloseState->addTransition(RL_Coruscate, SIGNAL(timeout()), Red_State);

     //黄灯闪烁
     YL_Coruscate = new QTimer;
     YL_Coruscate->setSingleShot(true);
     YL_Coruscate->setInterval(521);
     connect(Yellow_State,SIGNAL(entered()) , YL_Coruscate , SLOT(start()));
     Yellow_State->addTransition(YL_Coruscate, SIGNAL(timeout()) , YellowCloseState);

     connect(YellowCloseState,SIGNAL(entered()) , YL_Coruscate , SLOT(start()));
     YellowCloseState->addTransition(YL_Coruscate, SIGNAL(timeout()) , Yellow_State);

     //绿灯闪烁
     GL_Coruscate = new QTimer;
     GL_Coruscate->setSingleShot(true);
     GL_Coruscate->setInterval(521);
     connect(Green_State,SIGNAL(entered()) , GL_Coruscate , SLOT(start()));
     Green_State->addTransition(GL_Coruscate,SIGNAL(timeout()),GreenCloseState);

     connect(GreenCloseState,SIGNAL(entered()) , GL_Coruscate , SLOT(start()));
     GreenCloseState->addTransition(GL_Coruscate,SIGNAL(timeout()),Green_State);
//闪烁状态初始化完毕********************************************************************************//

//各个状态之间的切换
     //各个状态之间的转换
     RtoCoru = new QTimer;
     RtoCoru->setSingleShot(true);
     RtoCoru->setInterval(msec_keepRed * 1000);
     //红状态---》红闪烁
     connect(RedState,SIGNAL(entered ()),RtoCoru,SLOT(start()));
     //更新LCD显示器上的数字
     connect(RedState,SIGNAL(entered()),this,SLOT(UpdateLcdFigure()));
     //启动倒计时程序
     connect(RedState , SIGNAL(entered()),LcdTimer,SLOT(start()));
     RedState->addTransition(RtoCoru, SIGNAL(timeout()), RedCoruscate);


     //红闪烁---》黄状态
     KeepRCoru = new QTimer(this);
     KeepRCoru->setSingleShot(true);
     KeepRCoru->setInterval(msec_Red * 1024 + 521);
     connect(RedCoruscate,SIGNAL(entered()),KeepRCoru,SLOT(start()));
     RedCoruscate->addTransition(KeepRCoru,SIGNAL(timeout()),YellowState);
     //终止红色闪烁时间
     connect(KeepRCoru,SIGNAL(timeout()),RL_Coruscate,SLOT(stop()));
     //终止红色倒计时程序
     connect(KeepRCoru,SIGNAL(timeout()),LcdTimer,SLOT(stop()));

     //黄状态---》黄闪烁
     YtoCoru = new QTimer;
     YtoCoru->setSingleShot(true);
     YtoCoru->setInterval( msec_keepYellow * 1000);
     connect(YellowState,SIGNAL(entered()),YtoCoru,SLOT(start()));
     connect(YellowState,SIGNAL(entered()),this,SLOT(UpdateLcdFigure()));
     //启动倒计时
     connect(YellowState,SIGNAL(entered()),LcdTimer,SLOT(start()));
     YellowState->addTransition(YtoCoru,SIGNAL(timeout()),YellowCoruscate);

     //黄闪烁---》绿状态
     KeepYCoru = new QTimer(this);
     KeepYCoru->setSingleShot(true);
     KeepYCoru->setInterval(msec_Yellow * 1024 + 521);
     connect(YellowCoruscate,SIGNAL(entered()),KeepYCoru,SLOT(start()));
     YellowCoruscate->addTransition(KeepYCoru,SIGNAL(timeout()),GreenState);
     //终止黄色闪烁时间
     connect(KeepYCoru,SIGNAL(timeout()),YL_Coruscate,SLOT(stop()));
     //终止黄色倒计时
     connect(KeepYCoru,SIGNAL(timeout()),LcdTimer,SLOT(stop()));

     //绿状态---》绿闪烁
     GtoCoru = new QTimer;
     GtoCoru->setSingleShot(true);
     GtoCoru->setInterval(msec_keepGreen * 1000);
     connect(GreenState,SIGNAL(entered()),GtoCoru,SLOT(start()));
     connect(GreenState,SIGNAL(entered()),this,SLOT(UpdateLcdFigure()));
     connect(GreenState,SIGNAL(entered()),LcdTimer,SLOT(start()));
     GreenState->addTransition(GtoCoru,SIGNAL(timeout()),GreenCoruscate);

     //绿闪烁---》红状态
     KeepGCoru =new QTimer(this);
     KeepGCoru->setSingleShot(true);
     KeepGCoru->setInterval(msec_Green * 1024 + 521);
     connect(GreenCoruscate,SIGNAL(entered()),KeepGCoru,SLOT(start()));
     GreenCoruscate->addTransition(KeepGCoru,SIGNAL(timeout()),RedState);
     //终止绿色闪烁时间
     connect(KeepGCoru,SIGNAL(timeout()) , GL_Coruscate,SLOT(stop()));
     //终止绿色倒计时
     connect(KeepGCoru,SIGNAL(timeout()) , LcdTimer,SLOT(stop()));

     machine = new QStateMachine(this);
     machine->addState(RedState);
     machine->addState(RedCoruscate);

     machine->addState(YellowState);
     machine->addState(YellowCoruscate);

     machine->addState(GreenState);
     machine->addState(GreenCoruscate);

     machine->setInitialState(RedState);
    //把灯放如镜头
     scene->addItem(light);
     //初始化自定义场景，可以更灵活的显示要显示的内容
     view = new MyView(scene);
     view->setScene(scene);
     view->resize(G_w , G_h*3);
//左窗口布局
     QVBoxLayout *LeftLayout = new QVBoxLayout(this);
     lcdNumber = new QLCDNumber(this);
     //设置允许自动填充背景色
     lcdNumber->setAutoFillBackground(true);
     //设置LCD最小高度
     lcdNumber->setMinimumHeight(31);

     //lcdNumber->setForegroundRole(QPalette::Foreground);
     //设置组件绘制背景颜色 用调色板(palette) 里面的background color;
     /*
        Outline	Produces raised segments filled with the background color
        Filled (this is the default).	Produces raised segments filled with the foreground color.
        Flat	Produces flat segments filled with the foreground color.
     */
     lcdNumber->setSegmentStyle(QLCDNumber::Outline);
     //设置LCD数字的绘制颜色 用调色板(palette) 里面的Foreground color;
     lcdNumber->setSegmentStyle(QLCDNumber::Flat);
     lcdNumber->setFrameStyle(QFrame::NoFrame);
     //得到LCD的调色板palette
     QPalette pal = lcdNumber->palette();
     //设置调色板的背景色
     pal.setColor(QPalette::Background,QColor(60,196,155));
     pal.setBrush(QPalette::Background,QColor(60,196,155));
     //设置调色板的前景色为蓝色
     pal.setColor(QPalette::Foreground,QColor(75,38,217));
     pal.setBrush(QPalette::Foreground,QColor(75,38,217));

     //把重新设置的调色板设置给LCD
     lcdNumber->setPalette(pal);
    // lcdNumber->update();

     QTimer *timer = new QTimer;
     connect(timer , SIGNAL(timeout()) , scene , SLOT(update()));
     timer->start(100/33);


     LeftLayout->addWidget(lcdNumber);
     LeftLayout->addWidget(view);
     setLayout(LeftLayout);

}

void RGBLight::slotStartMachine(int RedTime, int YellowTime, int GreenTime,
                                int RedStat, int YellowStat, int GreenStat, int state)
{
    qDebug()<<"slotStartMachine";
    if (state == 0) //state == 0 表示发送重置信号
    {
        if( machine->isRunning() )
        {
            int ret = QMessageBox::question(this,tr("提示"),
                                     tr("状态机已在运行，若无特殊情况，不建议强行更改！\n\t是否强行更改？"),
                                  QMessageBox::Ok | QMessageBox::Cancel);
            switch(ret)
            {
            case QMessageBox::Ok:
                QMessageBox::warning(this,tr("提醒"),
                                     tr("强行更改给您带来不便，\n本程序设计人员概不负责！"));

                break;
            case QMessageBox::Cancel:
                return ;
                break;
            default:
                qDebug()<<tr("出错了！");
            }
        }

        //闪烁次数
        msec_Red = RedTime;
        msec_Yellow = YellowTime;
        msec_Green = GreenTime;

        //保持闪烁
        KeepRCoru->setInterval(RedTime * 1024 + 521);
        KeepYCoru->setInterval(YellowTime * 1024 + 521);
        KeepGCoru->setInterval(GreenTime * 1024 + 521);
        //保持停滞时间
        msec_keepRed  = RedStat;
        msec_keepYellow = YellowStat;
        msec_keepGreen = GreenStat ;
        RtoCoru->setInterval(msec_keepRed * 1000);
        YtoCoru->setInterval(msec_keepYellow * 1000);
        GtoCoru->setInterval(msec_keepGreen * 1000);
    }

    if(state == 1)
    {
        //启动状态机
        machine->start();
        //闪烁次数
        msec_Red = RedTime;
        msec_Yellow = YellowTime;
        msec_Green = GreenTime;

        //保持闪烁
        KeepRCoru->setInterval(RedTime * 1024 + 521);
        KeepYCoru->setInterval(YellowTime * 1024 + 521);
        KeepGCoru->setInterval(GreenTime * 1024 + 521);
        //保持停滞时间
        msec_keepRed  = RedStat;
        msec_keepYellow = YellowStat;
        msec_keepGreen = GreenStat ;
        RtoCoru->setInterval(msec_keepRed * 1000);
        YtoCoru->setInterval(msec_keepYellow * 1000);
        GtoCoru->setInterval(msec_keepGreen * 1000);
    }
}
void RGBLight::slotStopMachine()
{
    qDebug()<<"slotStopMachine";
    machine->stop();
    LcdTimer->stop();
    //各灯闪烁子状态时间的切换
    RL_Coruscate->stop();
    YL_Coruscate->stop();
    GL_Coruscate->stop();

    //父状态闪烁
    RtoCoru->stop();
    YtoCoru->stop();
    GtoCoru->stop();

    //闪烁保持
    KeepRCoru->stop();
    KeepYCoru->stop();
    KeepGCoru->stop();
}
//显示数据
void RGBLight::LcdDisplayNumber(int LCDshow)
{
   // qDebug()<<"LcdDisplayNumber";
    if(LCDshow <= 3)
    {
        QPalette pal = lcdNumber->palette();
        //设置调色板的背景色
        pal.setColor(QPalette::Background,QColor(234,64,21));
        pal.setBrush(QPalette::Background,QColor(234,64,21));
        pal.setColor(QPalette::Foreground,QColor(251,251,4));
        pal.setBrush(QPalette::Foreground,QColor(251,251,4));
        lcdNumber->setPalette(pal);
    }else
    {
        QPalette pal = lcdNumber->palette();
        //设置调色板的背景色
        pal.setColor(QPalette::Background,QColor(60,196,155));
        pal.setBrush(QPalette::Background,QColor(60,196,155));
        pal.setColor(QPalette::Foreground,QColor(75,38,217));
        pal.setBrush(QPalette::Foreground,QColor(75,38,217));
        lcdNumber->setPalette(pal);
    }
    lcdNumber->display(LCDshow);
}
//更新每种状态的时间
void RGBLight::UpdateLcdFigure()
{
    qDebug()<<"UpdateLcdFigure";
    //sender():谁发送信号，它返回谁
    QState *TempState = static_cast<QState *>(sender());

    if(TempState == RedState)
    {   //                 停滞状态           保持闪烁状态
        LcdCount = ( RtoCoru->interval() + KeepRCoru->interval() ) / 1000;
    }else if(TempState == YellowState)
    {
        LcdCount = ( YtoCoru->interval() + KeepYCoru->interval() ) / 1000;
    }else if(TempState == GreenState)
    {
        LcdCount = ( GtoCoru->interval() + KeepGCoru->interval() ) / 1000;
    }
    qDebug()<<"LcdCOunt = "<<LcdCount;
    emit sendLcdNumber(LcdCount);

}
//每秒减一
void RGBLight::UpdateLcdNumber()
{
    emit sendLcdNumber(--LcdCount);
}
