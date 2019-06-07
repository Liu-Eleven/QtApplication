#include "driftbottle.h"

DriftBottle::DriftBottle( QWidget * parent ):
    QWidget(parent)

{
    setWindowTitle(tr("Ư �� ƿ"));
    setWindowIcon(QIcon(":/11.ico"));
    InitializeInterface();




}

DriftBottle::~DriftBottle()
{

}

void DriftBottle::InitializeInterface()
{
    //����һ��ͼƬ
    QPixmap image(":/Main.bmp");
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(image)));
    setPalette(palette);
    //this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QFont font("ZYSong18030",11);
    font.setBold(true);
    setFont(font);


    //��һ��
    chuckBottle = new QToolButton(this);
    chuckBottle->setGeometry(0,0,0,0);
    chuckBottle->setAutoRaise(true);
    chuckBottle->setText(tr("��һ��"));
    chuckBottle->setIcon(QPixmap(":/bottle.bmp"));
    chuckBottle->setIconSize(QPixmap(":/bottle.bmp").size());
    chuckBottle->setAutoRaise(true);
    chuckBottle->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    connect(chuckBottle,SIGNAL(clicked()),this,SLOT(slotChuckBottle()));
    //��һ��
    refloatation = new QToolButton(this);
    refloatation->setText(tr("���̿�"));
    refloatation->setIcon(QPixmap(":/net.bmp"));
    refloatation->setIconSize(QPixmap(":/net.bmp").size());
    refloatation->setAutoRaise(true);
    refloatation->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //λ��
    local = new QToolButton(this);
    local->setIcon(QPixmap(":/local.bmp"));
    local->setIconSize(QPixmap(":/local.bmp").size());
    local->setAutoRaise(true);
    local->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //�ҵ�ƿ��
    myBottle = new QToolButton(this);
    myBottle->setText(tr("�ҵ�ƿ��"));
    myBottle->setIcon(QPixmap(":/mybottle.bmp"));
    myBottle->setIconSize(QPixmap(":/mybottle.bmp").size());
    myBottle->setAutoRaise(true);
    myBottle->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addStretch();
    layout->addWidget(chuckBottle);
    layout->addWidget(refloatation);
    layout->addWidget(local);
    layout->addWidget(myBottle);
    layout->addStretch();

    MainLayout = new QVBoxLayout(this);

    MainLayout->addStretch();
    MainLayout->addStretch();
    MainLayout->addStretch();
    MainLayout->addLayout(layout);
    MainLayout->addStretch();

    setLayout(MainLayout);


    //statusBar()->showMessage(tr("����״̬��"));
    setMinimumSize(image.width(),image.height());
    setMaximumSize(image.width(),image.height());
}

void DriftBottle::slotChuckBottle()
{
    QMessageBox::about(this,tr("��һ��"),tr("����һ���ɣ�"));
}



























/* QImage image;
imageLabel = new QLabel(tr("LSY"));
//imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
//�����Ƿ�������С�Զ��������С
imageLabel->setScaledContents(true);

imageLabel->setPixmap(QPixmap::fromImage(image));
resize(image.width(), image.height());

setCentralWidget(imageLabel);*/

/* QGridLayout *layout = new QGridLayout;
QLabel *label2 = new QLabel(tr("�Ҳ���"));
QPushButton *btn = new QPushButton(tr("��ť����"));
layout->addWidget(btn,0,0,1,1);
layout->addWidget(label2,5,0,1,1);*/
