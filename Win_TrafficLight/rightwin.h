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
    QSpinBox *RedState;//�����ʱ��
    QSpinBox *RedCoru;//��˸ʱ��

    QSpinBox *YellowState;//�Ƶ���ʱ��
    QSpinBox *YellowCoru;//��˸ʱ��

    QSpinBox *GreenState;//�̵���ʱ��
    QSpinBox *GreenCoru;//��˸ʱ��

};

#endif // RIGHTWIN_H
