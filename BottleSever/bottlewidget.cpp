#include "bottlewidget.h"

BottleWidget::BottleWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("漂流瓶服务器"));
    resize(200 , 100);

    label = new QLabel(tr("本机IP地址"));
    quitBtn = new QPushButton(tr("退出"));

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(label);
    layout->addWidget(quitBtn);

    setLayout(layout);
}
BottleWidget::~BottleWidget()
{
}
