#ifndef PICTRANS_H
#define PICTRANS_H

#include <QtGui>

class PicTrans : public QDialog
{
    Q_OBJECT

public:
    PicTrans(QWidget *parent = 0);
    ~PicTrans();
    void paintEvent(QPaintEvent *);

private slots:
    void SlotChanged(int);
private:
    QImage *img;
    QImage dest;
};

#endif // PICTRANS_H
