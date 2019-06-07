#include "textalign.h"
#include <QtTest>


TextAlign::TextAlign(QWidget *parent)
    : QMainWindow(parent)
{

    //设置窗口标题
    setWindowTitle(tr("设置字体对齐方式"));
    //设置窗口标题图标
    setWindowIcon(QIcon(":/T.ico"));

    QToolBar *toolBar = addToolBar("SetAlignment");

    //排序
    label = new QLabel(tr("排序："));
    listBox = new QComboBox(toolBar);
    //排序风格
    listBox->addItem(tr("标准"));
    listBox->addItem(tr("小圆点"));
    listBox->addItem(tr("小圆圈"));
    listBox->addItem(tr("四方块"));
    listBox->addItem(tr("数字"));
    listBox->addItem(tr("小写字母"));
    listBox->addItem(tr("大写字母"));
    toolBar->addWidget(label);
    toolBar->addWidget(listBox);

    //增加一个分隔符
    toolBar->addSeparator();

    //添加一个动作集合QActionGroup
    QActionGroup *actGrp = new QActionGroup(this);

    //文本左对齐
    leftAction = new QAction(QIcon(":/textleft.png"),tr("左对齐"),actGrp);
    leftAction->setCheckable(true);

    //文本居中
    centerAction = new QAction(QIcon(":/textcenter"),tr("居  中"),actGrp);
    centerAction->setCheckable(true);

    //正文文本
    justifyAction = new QAction(QIcon(":/textjustify"), tr("正  文"), actGrp);
    justifyAction->setCheckable(true);

    //文本右对齐
    rightAction = new QAction(QIcon(":/textright"), tr("右对齐"),actGrp);
    rightAction->setCheckable(true);

    //添加动作集合
    toolBar->addActions(actGrp->actions());


    //添加编辑工具栏
    QToolBar *editBar = addToolBar("EditBar");

    //前进
    redoAction = new QAction(QIcon(":/redo"),tr("恢复"),this);
    //后退
    undoAction = new QAction(QIcon(":/undo"),tr("撤销"),this);

    //添加动作
    editBar->addAction(redoAction);
    editBar->addAction(undoAction);

    //文本
    text = new QTextEdit(this);
    text->setFocus();
    setCentralWidget(text);

    //建立信号槽
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
       alignment()函数获得光标当前位置所处段落的对齐方式，设置相应对齐方式为按下状态。
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
      QTextListFormat主要用于描述文本的排序格式，主要包含两个属性：
      QTextListFormat::Style，表示文本采用哪种排序方式；
      QTextListFormat::indent(),表示排序后的缩进值。
    */

    //设置文本的排序方式
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
          以下代码为设置QTextListFormat的第二个属性indent，即缩进值，把设置的
          格式应用到光标所在的文本处，这段程序代码以beginEditBlock()开始，以endEditBlock()
          结束，这两个函数的作用是设定这两个函数之间的所有操作相当于一个动作，如果需要进行撤销或
          恢复，则这两个函数之间的所有操作将同时被撤销或恢复，这两个函数一般成对出现。

          设置QTextListFormat的缩进值首先通过QTextCursor获得QTextBlockFormat对象，
          由QTextBlockFormat获得段落的缩进值，在此基础上定义QTextListFormat的缩进值。

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

