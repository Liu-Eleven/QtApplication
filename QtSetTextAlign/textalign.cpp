#include "textalign.h"
#include <QtTest>


TextAlign::TextAlign(QWidget *parent)
    : QMainWindow(parent)
{

    //���ô��ڱ���
    setWindowTitle(tr("����������뷽ʽ"));
    //���ô��ڱ���ͼ��
    setWindowIcon(QIcon(":/T.ico"));

    QToolBar *toolBar = addToolBar("SetAlignment");

    //����
    label = new QLabel(tr("����"));
    listBox = new QComboBox(toolBar);
    //������
    listBox->addItem(tr("��׼"));
    listBox->addItem(tr("СԲ��"));
    listBox->addItem(tr("СԲȦ"));
    listBox->addItem(tr("�ķ���"));
    listBox->addItem(tr("����"));
    listBox->addItem(tr("Сд��ĸ"));
    listBox->addItem(tr("��д��ĸ"));
    toolBar->addWidget(label);
    toolBar->addWidget(listBox);

    //����һ���ָ���
    toolBar->addSeparator();

    //���һ����������QActionGroup
    QActionGroup *actGrp = new QActionGroup(this);

    //�ı������
    leftAction = new QAction(QIcon(":/textleft.png"),tr("�����"),actGrp);
    leftAction->setCheckable(true);

    //�ı�����
    centerAction = new QAction(QIcon(":/textcenter"),tr("��  ��"),actGrp);
    centerAction->setCheckable(true);

    //�����ı�
    justifyAction = new QAction(QIcon(":/textjustify"), tr("��  ��"), actGrp);
    justifyAction->setCheckable(true);

    //�ı��Ҷ���
    rightAction = new QAction(QIcon(":/textright"), tr("�Ҷ���"),actGrp);
    rightAction->setCheckable(true);

    //��Ӷ�������
    toolBar->addActions(actGrp->actions());


    //��ӱ༭������
    QToolBar *editBar = addToolBar("EditBar");

    //ǰ��
    redoAction = new QAction(QIcon(":/redo"),tr("�ָ�"),this);
    //����
    undoAction = new QAction(QIcon(":/undo"),tr("����"),this);

    //��Ӷ���
    editBar->addAction(redoAction);
    editBar->addAction(undoAction);

    //�ı�
    text = new QTextEdit(this);
    text->setFocus();
    setCentralWidget(text);

    //�����źŲ�
    connect(listBox,SIGNAL(activated(int)),this,SLOT(slotList(int)));
    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(slotAlignment(QAction*)));

    connect(redoAction,SIGNAL(triggered()),text,SLOT(redo()));
    connect(undoAction,SIGNAL(triggered()),text,SLOT(undo()));

    connect(text->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(text->document(),SIGNAL(undoAvailable(bool)),undoAction,SLOT(setEnabled(bool)));

    connect(text,SIGNAL(cursorPositionChanged()),this,SLOT(slotCursorPositionChanged()));
   QTest::qSleep(2000);
}

TextAlign::~TextAlign()
{

}

void TextAlign::slotAlignment(QAction *act)
{
    qDebug()<<"slotAlignment";

    if( act == leftAction )
        text->setAlignment(Qt::AlignLeft);

    if( act == centerAction )
        text->setAlignment(Qt::AlignCenter);

    if( act == justifyAction )
        text->setAlignment(Qt::AlignJustify);

    if( act == rightAction )
        text->setAlignment(Qt::AlignRight);

}

void TextAlign::slotCursorPositionChanged()
{
    qDebug()<<"slotCursorPositionChanged";
    /*
       alignment()������ù�굱ǰλ����������Ķ��뷽ʽ��������Ӧ���뷽ʽΪ����״̬��
    */
    if(text->alignment() == Qt::AlignLeft)
        leftAction->setChecked(true);

    if(text->alignment() == Qt::AlignCenter )
        centerAction->setChecked(true);

    if(text->alignment() == Qt::AlignJustify )
        justifyAction->setChecked(true);

    if(text->alignment() == Qt::AlignRight )
        rightAction->setChecked(true);

}


void TextAlign::slotList(int index)
{
    qDebug()<<"slotList";
    QTextCursor cursor = text->textCursor();
    /*
      QTextListFormat��Ҫ���������ı��������ʽ����Ҫ�����������ԣ�
      QTextListFormat::Style����ʾ�ı�������������ʽ��
      QTextListFormat::indent(),��ʾ����������ֵ��
    */

    //�����ı�������ʽ
    if(index != 0)
    {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch(index)
        {
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            style = QTextListFormat::ListDecimal;
            break;
        case 5:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style = QTextListFormat::ListUpperAlpha;
            break;
        default:
            qDebug("slotList error ");

        }


        /*
          ���´���Ϊ����QTextListFormat�ĵڶ�������indent��������ֵ�������õ�
          ��ʽӦ�õ�������ڵ��ı�������γ��������beginEditBlock()��ʼ����endEditBlock()
          �������������������������趨����������֮������в����൱��һ�������������Ҫ���г�����
          �ָ���������������֮������в�����ͬʱ��������ָ�������������һ��ɶԳ��֡�

          ����QTextListFormat������ֵ����ͨ��QTextCursor���QTextBlockFormat����
          ��QTextBlockFormat��ö��������ֵ���ڴ˻����϶���QTextListFormat������ֵ��

        */
        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;

        if( cursor.currentList() )
        {
            listFmt = cursor.currentList()->format();
        }else
        {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();

    }else
    {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }



}

