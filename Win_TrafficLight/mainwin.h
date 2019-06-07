#ifndef MAINWIN_H
#define MAINWIN_H

//#include <QWidget>
#include "leftwin.h"
#include "rightwin.h"

class MainWin : public QFrame
{
    Q_OBJECT
public:
    explicit MainWin(QWidget *parent = 0);

signals:

public slots:
private:
    RGBLight *leftWin;
    RightWin *rightwindow;

};

#endif // MAINWIN_H
