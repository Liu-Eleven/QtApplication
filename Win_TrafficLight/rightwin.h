#ifndef RIGHTWIN_H
#define RIGHTWIN_H

#include <QtGui>

class RightWin : public QWidget
{
    Q_OBJECT
public:
    explicit RightWin(QWidget *parent = 0);

    QPushButton *StartBtn;
    QPushButton *StopBtn;
    QPushButton *ResetBtn;

signals:
    void startStateMachine(int , int , int,int ,int ,int, int);
    void stopStateMachine();

public slots:
    void startMachine();
    void stopMachine();
    void ResetParameter();



private:
    QSpinBox *RedState;//红灯总时间
    QSpinBox *RedCoru;//闪烁时间

    QSpinBox *YellowState;//黄灯总时间
    QSpinBox *YellowCoru;//闪烁时间

    QSpinBox *GreenState;//绿灯总时间
    QSpinBox *GreenCoru;//闪烁时间

};

#endif // RIGHTWIN_H
