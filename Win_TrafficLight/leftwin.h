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
    void LcdDisplayNumber(int );//显示数据
    void UpdateLcdFigure();//更新每种状态的时间
    void UpdateLcdNumber();

private:
    void CreatLight();

    QGraphicsScene *scene;
    MyLight *light;
    MyView *view;
    QStateMachine *machine ;
    QLCDNumber *lcdNumber;

    //各灯状态
    QState *RedState;
    QState *YellowState;
    QState *GreenState;

    //各灯闪烁子状态时间的切换
    QTimer *RL_Coruscate;
    QTimer *YL_Coruscate;
    QTimer *GL_Coruscate;

    //父状态闪烁
    QTimer *RtoCoru;
    QTimer *YtoCoru;
    QTimer *GtoCoru;

    //闪烁保持
    QTimer *KeepRCoru;
    QTimer *KeepYCoru;
    QTimer *KeepGCoru;

    //每秒更新
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
