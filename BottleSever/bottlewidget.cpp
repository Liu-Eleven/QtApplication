#include "bottlewidget.h"

BottleWidget::BottleWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("Ư��ƿ������"));
    resize(200 , 100);

    label = new QLabel(tr("����IP��ַ"));
    quitBtn = new QPushButton(tr("�˳�"));

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(label);
    layout->addWidget(quitBtn);

    setLayout(layout);
}
BottleWidget::~BottleWidget()
{
}
