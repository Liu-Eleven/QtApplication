#ifndef DRIFTBOTTLE_H
#define DRIFTBOTTLE_H

#include <QtGui>

class DriftBottle : public QWidget
{
    Q_OBJECT

public:
    DriftBottle( QWidget * parent = 0 );
    ~DriftBottle();
private slots :
    void slotChuckBottle();
private:
    //扔一个
    QToolButton *chuckBottle;
    //捞一捞
    QToolButton *refloatation;
    //本地
    QToolButton *local;
    //我的瓶子
    QToolButton *myBottle;

    QVBoxLayout *MainLayout;

    void InitializeInterface();
};

#endif // DRIFTBOTTLE_H
