#include <QtGui>
#include "mysetfont.h"

MySetFont::MySetFont(QWidget *parent)
    : QMainWindow(parent)
{
    QFont font("ZYSong18030",12);
    setFont(font);
    //设置标题图片
    setWindowIcon(QIcon(":/BIN.ico"));

    setWindowTitle(tr("Qt字体设置"));

    QToolBar *toolBar = addToolBar("字体工具栏");

            /*字体*/
    label1 = new QLabel(tr("字体："));
    fontBox = new QFontComboBox(toolBar);

    //过滤，只在下拉列表中显示某一类字体，默认为QFontComboBox::AllFonts所有字体
    /*以我目前的水平和我的实验，加与不加没啥区别！！！*/
    fontBox->setFontFilters(QFontComboBox::ScalableFonts);
    toolBar->addWidget(label1);
    toolBar->addWidget(fontBox);

            /*字号*/
    label2 = new QLabel(tr("字号："));
    sizeBox = new QComboBox(toolBar);
    toolBar->addWidget(label2);
    toolBar->addWidget(sizeBox);

    //QFontDatabase:当前系统中所有可用的格式信息，主要是字体的字号大小
    QFontDatabase db;
    //standardSizes():返回可用的标准字号列表
    foreach (int size, db.standardSizes() )
    {
        sizeBox->addItem(QString::number(size));
    }
        /*增加分隔符*/
    toolBar->addSeparator();

    /*加粗、斜体、下画线、颜色*/
    boldBtn = new QToolButton ;
    boldBtn->setIcon(QIcon(":/bold.png"));
    boldBtn->setCheckable(true);//boldBtn->setChecked(true);以前写的就是这，但是有误
    toolBar->addWidget(boldBtn);

    italicBtn = new QToolButton(this);
    italicBtn->setIcon(QIcon(":/italic.png"));
    italicBtn->setCheckable(true);
    toolBar->addWidget(italicBtn);

    underBtn = new QToolButton(this) ;
    underBtn->setIcon(QIcon(":/underline.png"));
    underBtn->setCheckable(true);
    toolBar->addWidget(underBtn);

    toolBar->addSeparator();
    colorBtn = new QToolButton(this);
    colorBtn->setIcon(QIcon(":/color.png"));
    toolBar->addWidget(colorBtn);

    text = new QTextEdit(this);
    text->setFocus();
    setCentralWidget(text);

    connect(fontBox,SIGNAL(activated(QString)), this,SLOT(slotFont(QString)));
    connect(sizeBox,SIGNAL(activated(QString)), this,SLOT(slotSize(QString)));
    connect(boldBtn,SIGNAL(clicked()), this , SLOT(slotBold()));
    connect(italicBtn,SIGNAL(clicked()),this,SLOT(slotItalic()));
    connect(underBtn,SIGNAL(clicked()),this,SLOT(slotUnder()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(slotColor()));

    //当光标所在位置的字符格式发生变化时触发此信号,即光标位置发生改编后，新位置字符格式与
    //之前位置的不一样时触发此信号
    connect(text,SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this,SLOT(slotCurrentFormatChanged(QTextCharFormat)));
}

MySetFont::~MySetFont()
{

}
//设置字体
void MySetFont::slotFont(QString f)
{
    qDebug()<<tr("设置字体");
    QTextCharFormat fmt;
    fmt.setFontFamily(f);//选择字体名称设置给QTextCharFormat对象。
    mergeFormat(fmt);//把新的格式应用到光标选择区域内的字符
}

//字体大小
void MySetFont::slotSize(QString num)
{
    qDebug()<<tr("设置字体大小");
    QTextCharFormat fmt;
    fmt.setFontPointSize(num.toFloat());
    mergeFormat(fmt);
}

//加粗字体
void MySetFont::slotBold()
{
    qDebug()<<tr("设置粗体");
    /*
      文字的粗细值由 QFont::Weight 表示，它是一个整型值，可为0~99，
      它有5个预置的值：
      QFont::Light <25>
      QFont::Normal <50>
      QFont::DemiBold <63>
      QFont::Bold <75>
      QFont::Black <87>
      一般在QFont::Normal和QFont::Bold之间转换，此处调用QTextCharFormat的
      setFontWeight()函数设置粗细值。
    */
    QTextCharFormat fmt;
    fmt.setFontWeight(boldBtn->isChecked() ? QFont::Bold : QFont::Normal);
    //boldBtn->isChecked() ? QFont::Bold : QFont::Normal
    mergeFormat(fmt);
}

//设置斜体
void MySetFont::slotItalic()
{
    qDebug()<<tr("设置倾斜");
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    mergeFormat(fmt);

}

void MySetFont::slotUnder()
{
    qDebug()<<tr("添加下划线");
    QTextCharFormat fmt;
    fmt.setFontUnderline(underBtn->isChecked());
    mergeFormat(fmt);
}

void MySetFont::slotColor()
{
    qDebug()<<tr("设置字体颜色");
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        mergeFormat(fmt);
    }
}

void MySetFont::mergeFormat(QTextCharFormat format)
{
    qDebug()<<tr("获取选择字符");
    /*QTextCursor:用来表示编辑文本框中的光标
      所有对于QTextDocument进行的修改都通过QTextCursor类来完成，mergeFormat()函数的作用
      即利用QTextCursor类把所有新的格式应用到光标选择区内的字符上，每个格式设置槽函数最后都需要
      调用此函数来应用更新。
      关于获取编辑框中的光标，若光标没有高亮选择区则把光标所在处的词作为选区，由前后空格或“，”、“.”
      等标点符号区分词。调用QTextCursor的mergeCharFormat()函数把参数format所表示的格式应用到
      光标所在处的字符上，最后调用QTextEdit的mergeCurrentCharFormat()函数把格式应用到选区内的所有
      字符上。

    */
    QTextCursor cursor = text->textCursor();
    if( !cursor.hasSelection() )
    {
        /*
QTextCursor::Document	        3	Selects the entire document.
QTextCursor::BlockUnderCursor	2	Selects the block of text under the cursor.
QTextCursor::LineUnderCursor	1	Selects the line of text under the cursor.
QTextCursor::WordUnderCursor	0	Selects the word under the cursor. If the
                                        cursor is not positioned within a string of
                                        selectable characters, no text is selected.
        */
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    text->mergeCurrentCharFormat(format);
}

void MySetFont::slotCurrentFormatChanged(const QTextCharFormat &fmt)
{
    qDebug()<<"6";
    fontBox->setCurrentIndex(fontBox->findText(fmt.fontFamily()));
    sizeBox->setCurrentIndex(sizeBox->findText(QString::number(fmt.FontPointSize)));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underBtn->setChecked(fmt.fontUnderline());
}

