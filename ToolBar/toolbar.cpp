#include "ToolBar.h"

ToolBar::ToolBar(QWidget *parent)
    : QMainWindow(parent)
{
    //���ñ���
    setWindowTitle(tr("�ڹ�������Ƕ��ؼ�"));
    //�ı����ͼ��
    setWindowIcon(QIcon(":/ABS utility.ico"));

    text = new QTextEdit(this);
    //�����ı��༭��Ϊֻ��
    text->setReadOnly(true);
    setCentralWidget(text);

    //���ù�����
    QToolBar *TB = addToolBar("Control");

    QLabel *label1 = new QLabel(tr("�ؼ��٣�"));

    box = new QComboBox(this);
    box->insertItem(0,tr("����һ"));
    box->insertItem(1,tr("�κ���"));
    box->insertItem(2,tr("��  ��"));
    //����QComboBox����ѡ��
    box->setCurrentIndex(box->findText(tr("��  ��")));

    TB->addWidget(label1);
    TB->addWidget(box);

    TB->addSeparator();

    QLabel *label2 = new QLabel(tr("�ؼ��ڣ�"));

    spin = new QSpinBox(this);
    spin->setRange(1, 11);

    TB->addWidget(label2);
    TB->addWidget(spin);

    connect(box,SIGNAL(currentIndexChanged(QString)),
            this,SLOT(slotComboBox(QString)));

    connect(spin,SIGNAL(valueChanged(QString)),
            this,SLOT(slotSpinBox(QString)));


}

ToolBar::~ToolBar()
{

}

void ToolBar::slotComboBox(QString ComboStr)
{
    QString doc;
    QString spinStr;
    doc = "QComboBox:"+ComboStr+"\n"+"QSpinBox:"+spinStr.setNum(spin->value());
    text->setText(doc);
}
void ToolBar::slotSpinBox(QString value)
{
    QString doc;
    doc = "QComboBox:"+box->currentText() + "\n"+"QSpinBox:"+value;
    text->setText(doc);
}
