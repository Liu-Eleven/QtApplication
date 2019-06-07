#include <QtGui>
#include "mysetfont.h"

MySetFont::MySetFont(QWidget *parent)
    : QMainWindow(parent)
{
    QFont font("ZYSong18030",12);
    setFont(font);
    //���ñ���ͼƬ
    setWindowIcon(QIcon(":/BIN.ico"));

    setWindowTitle(tr("Qt��������"));

    QToolBar *toolBar = addToolBar("���幤����");

            /*����*/
    label1 = new QLabel(tr("���壺"));
    fontBox = new QFontComboBox(toolBar);

    //���ˣ�ֻ�������б�����ʾĳһ�����壬Ĭ��ΪQFontComboBox::AllFonts��������
    /*����Ŀǰ��ˮƽ���ҵ�ʵ�飬���벻��ûɶ���𣡣���*/
    fontBox->setFontFilters(QFontComboBox::ScalableFonts);
    toolBar->addWidget(label1);
    toolBar->addWidget(fontBox);

            /*�ֺ�*/
    label2 = new QLabel(tr("�ֺţ�"));
    sizeBox = new QComboBox(toolBar);
    toolBar->addWidget(label2);
    toolBar->addWidget(sizeBox);

    //QFontDatabase:��ǰϵͳ�����п��õĸ�ʽ��Ϣ����Ҫ��������ֺŴ�С
    QFontDatabase db;
    //standardSizes():���ؿ��õı�׼�ֺ��б�
    foreach (int size, db.standardSizes() )
    {
        sizeBox->addItem(QString::number(size));
    }
        /*���ӷָ���*/
    toolBar->addSeparator();

    /*�Ӵ֡�б�塢�»��ߡ���ɫ*/
    boldBtn = new QToolButton ;
    boldBtn->setIcon(QIcon(":/bold.png"));
    boldBtn->setCheckable(true);//boldBtn->setChecked(true);��ǰд�ľ����⣬��������
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

    //���������λ�õ��ַ���ʽ�����仯ʱ�������ź�,�����λ�÷����ı����λ���ַ���ʽ��
    //֮ǰλ�õĲ�һ��ʱ�������ź�
    connect(text,SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this,SLOT(slotCurrentFormatChanged(QTextCharFormat)));
}

MySetFont::~MySetFont()
{

}
//��������
void MySetFont::slotFont(QString f)
{
    qDebug()<<tr("��������");
    QTextCharFormat fmt;
    fmt.setFontFamily(f);//ѡ�������������ø�QTextCharFormat����
    mergeFormat(fmt);//���µĸ�ʽӦ�õ����ѡ�������ڵ��ַ�
}

//�����С
void MySetFont::slotSize(QString num)
{
    qDebug()<<tr("���������С");
    QTextCharFormat fmt;
    fmt.setFontPointSize(num.toFloat());
    mergeFormat(fmt);
}

//�Ӵ�����
void MySetFont::slotBold()
{
    qDebug()<<tr("���ô���");
    /*
      ���ֵĴ�ϸֵ�� QFont::Weight ��ʾ������һ������ֵ����Ϊ0~99��
      ����5��Ԥ�õ�ֵ��
      QFont::Light <25>
      QFont::Normal <50>
      QFont::DemiBold <63>
      QFont::Bold <75>
      QFont::Black <87>
      һ����QFont::Normal��QFont::Bold֮��ת�����˴�����QTextCharFormat��
      setFontWeight()�������ô�ϸֵ��
    */
    QTextCharFormat fmt;
    fmt.setFontWeight(boldBtn->isChecked() ? QFont::Bold : QFont::Normal);
    //boldBtn->isChecked() ? QFont::Bold : QFont::Normal
    mergeFormat(fmt);
}

//����б��
void MySetFont::slotItalic()
{
    qDebug()<<tr("������б");
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    mergeFormat(fmt);

}

void MySetFont::slotUnder()
{
    qDebug()<<tr("����»���");
    QTextCharFormat fmt;
    fmt.setFontUnderline(underBtn->isChecked());
    mergeFormat(fmt);
}

void MySetFont::slotColor()
{
    qDebug()<<tr("����������ɫ");
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
    qDebug()<<tr("��ȡѡ���ַ�");
    /*QTextCursor:������ʾ�༭�ı����еĹ��
      ���ж���QTextDocument���е��޸Ķ�ͨ��QTextCursor������ɣ�mergeFormat()����������
      ������QTextCursor��������µĸ�ʽӦ�õ����ѡ�����ڵ��ַ��ϣ�ÿ����ʽ���òۺ��������Ҫ
      ���ô˺�����Ӧ�ø��¡�
      ���ڻ�ȡ�༭���еĹ�꣬�����û�и���ѡ������ѹ�����ڴ��Ĵ���Ϊѡ������ǰ��ո�򡰣�������.��
      �ȱ��������ִʡ�����QTextCursor��mergeCharFormat()�����Ѳ���format����ʾ�ĸ�ʽӦ�õ�
      ������ڴ����ַ��ϣ�������QTextEdit��mergeCurrentCharFormat()�����Ѹ�ʽӦ�õ�ѡ���ڵ�����
      �ַ��ϡ�

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

