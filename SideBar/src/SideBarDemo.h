#ifndef SIDEBARDEMO_H
#define SIDEBARDEMO_H

#include <QWidget>
#include <QList>

class QToolButton;

namespace Ui {
    class SideBarDemo;
}

class SideBarDemo : public QWidget {
    Q_OBJECT

public:
    explicit SideBarDemo(QWidget *parent = 0);
    ~SideBarDemo();

private slots:
    void changeButtonStatus();

private:
    Ui::SideBarDemo *ui;
    QList<QToolButton *> buttons;

    void initButtons();
};

#endif // SIDEBARDEMO_H
