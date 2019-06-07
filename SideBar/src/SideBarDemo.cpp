#include "SideBarDemo.h"
#include "ui_SideBarDemo.h"

SideBarDemo::SideBarDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBarDemo) {
    ui->setupUi(this);
    initButtons();
}

SideBarDemo::~SideBarDemo() {
    delete ui;
}

void SideBarDemo::initButtons() {
    // 把按钮放在一个list里为了方便管理
    buttons.append(ui->toolButton_1);
    buttons.append(ui->toolButton_2);
    buttons.append(ui->toolButton_3);
    buttons.append(ui->toolButton_4);

    foreach (QToolButton *b, buttons) {
        connect(b, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));
    }

    ui->toolButton_1->setProperty("first", "true"); // 第一个按钮上面的边框不要.
    ui->toolButton_2->click(); // 第二个按钮被按下, 即设置它的current属性为true
}

void SideBarDemo::changeButtonStatus() {
    // 用按钮的current属性来控制被按下按钮的外观.
    // 当按钮被按下时, 设置其current属性为true,
    // 其他按钮的current属性为false, 为了更新按钮的外观.
    foreach (QToolButton *b, buttons) {
        b->setProperty("current", "false");
        b->setStyleSheet(""); // 刷新按钮的样式
    }


    QToolButton *source = qobject_cast<QToolButton *>(sender());
    source->setProperty("current", "true");
    source->setStyleSheet("");
}





