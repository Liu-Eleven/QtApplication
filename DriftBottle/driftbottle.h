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
    //��һ��
    QToolButton *chuckBottle;
    //��һ��
    QToolButton *refloatation;
    //����
    QToolButton *local;
    //�ҵ�ƿ��
    QToolButton *myBottle;

    QVBoxLayout *MainLayout;

    void InitializeInterface();
};

#endif // DRIFTBOTTLE_H
