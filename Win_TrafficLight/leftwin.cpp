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
    //��ʼ����ͷ
    scene->setSceneRect(0,0,G_w,G_h*3);
    scene->setBackgroundBrush(Qt::black);



    //����һ����
    light = new MyLight;
    //��ʼ���Ƶ�λ��
    light->setPos(50,50);
    //��ɫ״̬
    RedState = new QState;
    RedState->assignProperty(light,"color",Qt::red);
    RedState->assignProperty(light,"pos",QPoint(50,50));
    //��ɫ��˸״̬
    QState *RedCoruscate = new QState;
    //��ɫ��˸״̬��״̬
    QState *Red_State = new QState(RedCoruscate) ;
    QState *RedCloseState = new QState(RedCoruscate);

    //��ɫ״̬����λ��
    Red_State->assignProperty(light,"color",Qt::red);
    Red_State->assignProperty(light,"pos",QPoint(50,50));
    RedCloseState->assignProperty(light,"color",Qt::black);
    RedCloseState->assignProperty(light,"pos",QPoint(50,50));
    //������˸״̬��ʼ״̬
    RedCoruscate->setInitialState(Red_State);
//end red light initializtion****************************************************************//

    //��ɫ״̬
    YellowState = new QState;
    YellowState->assignProperty(light,"color",Qt::yellow);
    YellowState->assignProperty(light,"pos",QPoint(50,150));
    //��ɫ��˸״̬
    QState *YellowCoruscate = new QState;
    //��ɫ��˸״̬��״̬
    QState *Yellow_State = new QState(YellowCoruscate) ;
    QState *YellowCloseState = new QState(YellowCoruscate);

    Yellow_State->assignProperty(light,"color",Qt::yellow);
    Yellow_State->assignProperty(light,"pos",QPoint(50,150));
    YellowCloseState->assignProperty(light,"color",Qt::black);
    YellowCloseState->assignProperty(light,"pos",QPoint(50,150));
    //���û�ɫ״̬��ʼ״̬
    YellowCoruscate->setInitialState(Yellow_State);
// end yellow light initializtion**************************************************************//
    //��ɫ״̬
    GreenState = new QState;
    GreenState->assignProperty(light,"color",Qt::green);
    GreenState->assignProperty(light,"pos",QPoint(50,250));
    //��ɫ��˸״̬
     QState *GreenCoruscate = new QState;
    //��ɫ��˸״̬��״̬
     QState *Green_State = new QState(GreenCoruscate);
     QState *GreenCloseState = new QState(GreenCoruscate);

     Green_State->assignProperty(light,"color",Qt::green);
     Green_State->assignProperty(light,"pos",QPoint(50,250));
     GreenCloseState->assignProperty(light,"color",Qt::black);
     GreenCloseState->assignProperty(light,"pos",QPoint(50,250));
     //�趨��ɫ��˸״̬��ʼ״̬
     GreenCoruscate->setInitialState(Green_State);
//end green light initializtion ***************************************************************//


     //�����˸
     RL_Coruscate = new QTimer;
     RL_Coruscate->setSingleShot(true);
     RL_Coruscate->setInterval(521);

     connect(Red_State,SIGNAL(entered()), RL_Coruscate,SLOT(start()));
     Red_State->addTransition(RL_Coruscate,SIGNAL(timeout()),RedCloseState);

     connect(RedCloseState,SIGNAL(entered ()),RL_Coruscate,SLOT(start()));
     RedCloseState->addTransition(RL_Coruscate, SIGNAL(timeout()), Red_State);

     //�Ƶ���˸
     YL_Coruscate = new QTimer;
     YL_Coruscate->setSingleShot(true);
     YL_Coruscate->setInterval(521);
     connect(Yellow_State,SIGNAL(entered()) , YL_Coruscate , SLOT(start()));
     Yellow_State->addTransition(YL_Coruscate, SIGNAL(timeout()) , YellowCloseState);

     connect(YellowCloseState,SIGNAL(entered()) , YL_Coruscate , SLOT(start()));
     YellowCloseState->addTransition(YL_Coruscate, SIGNAL(timeout()) , Yellow_State);

     //�̵���˸
     GL_Coruscate = new QTimer;
     GL_Coruscate->setSingleShot(true);
     GL_Coruscate->setInterval(521);
     connect(Green_State,SIGNAL(entered()) , GL_Coruscate , SLOT(start()));
     Green_State->addTransition(GL_Coruscate,SIGNAL(timeout()),GreenCloseState);

     connect(GreenCloseState,SIGNAL(entered()) , GL_Coruscate , SLOT(start()));
     GreenCloseState->addTransition(GL_Coruscate,SIGNAL(timeout()),Green_State);
//��˸״̬��ʼ�����********************************************************************************//

//����״̬֮����л�
     //����״̬֮���ת��
     RtoCoru = new QTimer;
     RtoCoru->setSingleShot(true);
     RtoCoru->setInterval(msec_keepRed * 1000);
     //��״̬---������˸
     connect(RedState,SIGNAL(entered ()),RtoCoru,SLOT(start()));
     //����LCD��ʾ���ϵ�����
     connect(RedState,SIGNAL(entered()),this,SLOT(UpdateLcdFigure()));
     //��������ʱ����
     connect(RedState , SIGNAL(entered()),LcdTimer,SLOT(start()));
     RedState->addTransition(RtoCoru, SIGNAL(timeout()), RedCoruscate);


     //����˸---����״̬
     KeepRCoru = new QTimer(this);
     KeepRCoru->setSingleShot(true);
     KeepRCoru->setInterval(msec_Red * 1024 + 521);
     connect(RedCoruscate,SIGNAL(entered()),KeepRCoru,SLOT(start()));
     RedCoruscate->addTransition(KeepRCoru,SIGNAL(timeout()),YellowState);
     //��ֹ��ɫ��˸ʱ��
     connect(KeepRCoru,SIGNAL(timeout()),RL_Coruscate,SLOT(stop()));
     //��ֹ��ɫ����ʱ����
     connect(KeepRCoru,SIGNAL(timeout()),LcdTimer,SLOT(stop()));

     //��״̬---������˸
     YtoCoru = new QTimer;
     YtoCoru->setSingleShot(true);
     YtoCoru->setInterval( msec_keepYellow * 1000);
     connect(YellowState,SIGNAL(entered()),YtoCoru,SLOT(start()));
     connect(YellowState,SIGNAL(entered()),this,SLOT(UpdateLcdFigure()));
     //��������ʱ
     connect(YellowState,SIGNAL(entered()),LcdTimer,SLOT(start()));
     YellowState->addTransition(YtoCoru,SIGNAL(timeout()),YellowCoruscate);

     //����˸---����״̬
     KeepYCoru = new QTimer(this);
     KeepYCoru->setSingleShot(true);
     KeepYCoru->setInterval(msec_Yellow * 1024 + 521);
     connect(YellowCoruscate,SIGNAL(entered()),KeepYCoru,SLOT(start()));
     YellowCoruscate->addTransition(KeepYCoru,SIGNAL(timeout()),GreenState);
     //��ֹ��ɫ��˸ʱ��
     connect(KeepYCoru,SIGNAL(timeout()),YL_Coruscate,SLOT(stop()));
     //��ֹ��ɫ����ʱ
     connect(KeepYCoru,SIGNAL(timeout()),LcdTimer,SLOT(stop()));

     //��״̬---������˸
     GtoCoru = new QTimer;
     GtoCoru->setSingleShot(true);
     GtoCoru->setInterval(msec_keepGreen * 1000);
     connect(GreenState,SIGNAL(entered()),GtoCoru,SLOT(start()));
     connect(GreenState,SIGNAL(entered()),this,SLOT(UpdateLcdFigure()));
     connect(GreenState,SIGNAL(entered()),LcdTimer,SLOT(start()));
     GreenState->addTransition(GtoCoru,SIGNAL(timeout()),GreenCoruscate);

     //����˸---����״̬
     KeepGCoru =new QTimer(this);
     KeepGCoru->setSingleShot(true);
     KeepGCoru->setInterval(msec_Green * 1024 + 521);
     connect(GreenCoruscate,SIGNAL(entered()),KeepGCoru,SLOT(start()));
     GreenCoruscate->addTransition(KeepGCoru,SIGNAL(timeout()),RedState);
     //��ֹ��ɫ��˸ʱ��
     connect(KeepGCoru,SIGNAL(timeout()) , GL_Coruscate,SLOT(stop()));
     //��ֹ��ɫ����ʱ
     connect(KeepGCoru,SIGNAL(timeout()) , LcdTimer,SLOT(stop()));

     machine = new QStateMachine(this);
     machine->addState(RedState);
     machine->addState(RedCoruscate);

     machine->addState(YellowState);
     machine->addState(YellowCoruscate);

     machine->addState(GreenState);
     machine->addState(GreenCoruscate);

     machine->setInitialState(RedState);
    //�ѵƷ��羵ͷ
     scene->addItem(light);
     //��ʼ���Զ��峡�������Ը�������ʾҪ��ʾ������
     view = new MyView(scene);
     view->setScene(scene);
     view->resize(G_w , G_h*3);
//�󴰿ڲ���
     QVBoxLayout *LeftLayout = new QVBoxLayout(this);
     lcdNumber = new QLCDNumber(this);
     //���������Զ���䱳��ɫ
     lcdNumber->setAutoFillBackground(true);
     //����LCD��С�߶�
     lcdNumber->setMinimumHeight(31);

     //lcdNumber->setForegroundRole(QPalette::Foreground);
     //����������Ʊ�����ɫ �õ�ɫ��(palette) �����background color;
     /*
        Outline	Produces raised segments filled with the background color
        Filled (this is the default).	Produces raised segments filled with the foreground color.
        Flat	Produces flat segments filled with the foreground color.
     */
     lcdNumber->setSegmentStyle(QLCDNumber::Outline);
     //����LCD���ֵĻ�����ɫ �õ�ɫ��(palette) �����Foreground color;
     lcdNumber->setSegmentStyle(QLCDNumber::Flat);
     lcdNumber->setFrameStyle(QFrame::NoFrame);
     //�õ�LCD�ĵ�ɫ��palette
     QPalette pal = lcdNumber->palette();
     //���õ�ɫ��ı���ɫ
     pal.setColor(QPalette::Background,QColor(60,196,155));
     pal.setBrush(QPalette::Background,QColor(60,196,155));
     //���õ�ɫ���ǰ��ɫΪ��ɫ
     pal.setColor(QPalette::Foreground,QColor(75,38,217));
     pal.setBrush(QPalette::Foreground,QColor(75,38,217));

     //���������õĵ�ɫ�����ø�LCD
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
    if (state == 0) //state == 0 ��ʾ���������ź�
    {
        if( machine->isRunning() )
        {
            int ret = QMessageBox::question(this,tr("��ʾ"),
                                     tr("״̬���������У��������������������ǿ�и��ģ�\n\t�Ƿ�ǿ�и��ģ�"),
                                  QMessageBox::Ok | QMessageBox::Cancel);
            switch(ret)
            {
            case QMessageBox::Ok:
                QMessageBox::warning(this,tr("����"),
                                     tr("ǿ�и��ĸ����������㣬\n�����������Ա�Ų�����"));

                break;
            case QMessageBox::Cancel:
                return ;
                break;
            default:
                qDebug()<<tr("�����ˣ�");
            }
        }

        //��˸����
        msec_Red = RedTime;
        msec_Yellow = YellowTime;
        msec_Green = GreenTime;

        //������˸
        KeepRCoru->setInterval(RedTime * 1024 + 521);
        KeepYCoru->setInterval(YellowTime * 1024 + 521);
        KeepGCoru->setInterval(GreenTime * 1024 + 521);
        //����ͣ��ʱ��
        msec_keepRed  = RedStat;
        msec_keepYellow = YellowStat;
        msec_keepGreen = GreenStat ;
        RtoCoru->setInterval(msec_keepRed * 1000);
        YtoCoru->setInterval(msec_keepYellow * 1000);
        GtoCoru->setInterval(msec_keepGreen * 1000);
    }

    if(state == 1)
    {
        //����״̬��
        machine->start();
        //��˸����
        msec_Red = RedTime;
        msec_Yellow = YellowTime;
        msec_Green = GreenTime;

        //������˸
        KeepRCoru->setInterval(RedTime * 1024 + 521);
        KeepYCoru->setInterval(YellowTime * 1024 + 521);
        KeepGCoru->setInterval(GreenTime * 1024 + 521);
        //����ͣ��ʱ��
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
    //������˸��״̬ʱ����л�
    RL_Coruscate->stop();
    YL_Coruscate->stop();
    GL_Coruscate->stop();

    //��״̬��˸
    RtoCoru->stop();
    YtoCoru->stop();
    GtoCoru->stop();

    //��˸����
    KeepRCoru->stop();
    KeepYCoru->stop();
    KeepGCoru->stop();
}
//��ʾ����
void RGBLight::LcdDisplayNumber(int LCDshow)
{
   // qDebug()<<"LcdDisplayNumber";
    if(LCDshow <= 3)
    {
        QPalette pal = lcdNumber->palette();
        //���õ�ɫ��ı���ɫ
        pal.setColor(QPalette::Background,QColor(234,64,21));
        pal.setBrush(QPalette::Background,QColor(234,64,21));
        pal.setColor(QPalette::Foreground,QColor(251,251,4));
        pal.setBrush(QPalette::Foreground,QColor(251,251,4));
        lcdNumber->setPalette(pal);
    }else
    {
        QPalette pal = lcdNumber->palette();
        //���õ�ɫ��ı���ɫ
        pal.setColor(QPalette::Background,QColor(60,196,155));
        pal.setBrush(QPalette::Background,QColor(60,196,155));
        pal.setColor(QPalette::Foreground,QColor(75,38,217));
        pal.setBrush(QPalette::Foreground,QColor(75,38,217));
        lcdNumber->setPalette(pal);
    }
    lcdNumber->display(LCDshow);
}
//����ÿ��״̬��ʱ��
void RGBLight::UpdateLcdFigure()
{
    qDebug()<<"UpdateLcdFigure";
    //sender():˭�����źţ�������˭
    QState *TempState = static_cast<QState *>(sender());

    if(TempState == RedState)
    {   //                 ͣ��״̬           ������˸״̬
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
//ÿ���һ
void RGBLight::UpdateLcdNumber()
{
    emit sendLcdNumber(--LcdCount);
}
