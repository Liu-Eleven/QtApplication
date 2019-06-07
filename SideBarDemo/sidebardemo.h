#ifndef SIDEBARDEMO_H
#define SIDEBARDEMO_H

#include <QtGui>

namespace Ui {
    class SideBarDemo;
}

class SideBarDemo : public QWidget
{
    Q_OBJECT

public:
    explicit SideBarDemo(QWidget *parent = 0);
    ~SideBarDemo();

private:
    Ui::SideBarDemo *ui;
};

#endif // SIDEBARDEMO_H
