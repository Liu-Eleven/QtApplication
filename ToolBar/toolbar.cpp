#include "ToolBar.h"

ToolBar::ToolBar(QWidget *parent)
    : QMainWindow(parent)
{
    //设置标题
    setWindowTitle(tr("在工具栏中嵌入控件"));
    //改变标题图标
    setWindowIcon(QIcon(":/ABS utility.ico"));

    text = new QTextEdit(this);
    //设置文本编辑框为只读
    text->setReadOnly(true);
    setCentralWidget(text);

    //设置工具栏
    QToolBar *TB = addToolBar("Control");

    QLabel *label1 = new QLabel(tr("控件①："));

    box = new QComboBox(this);
    box->insertItem(0,tr("刘世一"));
    box->insertItem(1,tr("任海征"));
    box->insertItem(2,tr("张  雅"));
    //设置QComboBox的首选项
    box->setCurrentIndex(box->findText(tr("张  雅")));

    TB->addWidget(label1);
    TB->addWidget(box);

    TB->addSeparator();

    QLabel *label2 = new QLabel(tr("控件②："));

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
