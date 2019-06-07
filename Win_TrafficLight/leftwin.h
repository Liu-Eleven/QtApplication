#ifndef RGBLIGHT_H
#define RGBLIGHT_H

#include "mylight.h"
#include <QtGui>

class RGBLight : public QWidget
{
    Q_OBJECT

public:
    RGBLight(QWidget *parent = 0);
    ~RGBLight();
signals:
    void sendLcdNumber(int);
public slots:
    void slotStartMachine(int , int , int , int ,int ,int, int);
    void slotStopMachine();
    void LcdDisplayNumber(int );//��ʾ����
    void UpdateLcdFigure();//����ÿ��״̬��ʱ��
    void UpdateLcdNumber();

private:
    void CreatLight();

    QGraphicsScene *scene;
    MyLight *light;
    MyView *view;
    QStateMachine *machine ;
    QLCDNumber *lcdNumber;

    //����״̬
    QState *RedState;
    QState *YellowState;
    QState *GreenState;

    //������˸��״̬ʱ����л�
    QTimer *RL_Coruscate;
    QTimer *YL_Coruscate;
    QTimer *GL_Coruscate;

    //��״̬��˸
    QTimer *RtoCoru;
    QTimer *YtoCoru;
    QTimer *GtoCoru;

    //��˸����
    QTimer *KeepRCoru;
    QTimer *KeepYCoru;
    QTimer *KeepGCoru;

    //ÿ�����
    QTimer *LcdTimer;

    int LcdCount ;
    int msec_Red;
    int msec_Yellow ;
    int msec_Green ;

    int msec_keepRed ;
    int msec_keepYellow ;
    int msec_keepGreen ;
};

#endif // RGBLIGHT_H
