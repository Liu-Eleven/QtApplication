#include "sidebardemo.h"
#include "ui_sidebardemo.h"

SideBarDemo::SideBarDemo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBarDemo)
{
   ui->setupUi(this);
}

SideBarDemo::~SideBarDemo()
{
    delete ui;
}
