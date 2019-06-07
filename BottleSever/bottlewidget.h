#ifndef BOTTLEWIDGET_H
#define BOTTLEWIDGET_H

#include <QtGui>

class BottleWidget : public QWidget
{
    Q_OBJECT
public:
    BottleWidget(QWidget *parent = 0);
    ~BottleWidget();

signals:

public slots:

private:
    QLabel *label;
    QPushButton *quitBtn;
    QPushButton *orderBtn;
    //Server *server;

};

#endif // BOTTLEWIDGET_H
