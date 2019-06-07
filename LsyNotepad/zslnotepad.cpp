#include "rhznotepad.h"
//#include <QtGui>
#include <QTest>

RHZNotepad::RHZNotepad()
{
    ReadSetting();
    setWindowIcon(QIcon(":/love.ico"));
    InitializeInterface();

    setMinimumSize(521,521);
    QTest::qSleep(4000);

    //setWindowTitle(tr("RHZAILSY"));
    //setUnifiedTitleAndToolBarOnMac(true);
}

RHZNotepad::~RHZNotepad()
{

}
//初始化程序界面
void RHZNotepad::InitializeInterface()
{
    textArea = new QTextEdit(this);
    textArea->setAcceptRichText(true);
    textArea->setTabStopWidth(40);

    //textArea->setStyleSheet("background-image::url(:/BackGround.jpg)");
    //textArea->setHtml("<body background= ./BackGround.jpg/></body>");

    //设置换行模式为不换行
    textArea->setLineWrapMode(QTextEdit::NoWrap);
    //设置水平滚动条和垂直滚动条
    textArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    textArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(textArea);

    connect(textArea->document(),SIGNAL(contentsChanged()),
            this,SLOT(TextAreaWasModified()));
    setCurrentFileName("");

    CreateActions();
    CreateMenus();
    CreateToolBars();
    CreateStatusBar();

    QTextCharFormat fmt;
    fmt.setFontPointSize(11);
    mergeFormat(fmt);
}

//建立菜单栏
void RHZNotepad::CreateMenus()
{
    //文件菜单
    FileMenu = menuBar()->addMenu(tr("文件(F)"));
    //添加动作
    FileMenu->addAction(newAct);
    FileMenu->addAction(OpenAct);
    FileMenu->addAction(SaveAct);
    FileMenu->addAction(SaveAsAct);
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAct);

    EditMenu = menuBar()->addMenu(tr("编辑(E)"));
    EditMenu->addAction(CutAct);
    EditMenu->addAction(CopyAct);
    EditMenu->addAction(PastAct);
    EditMenu->addSeparator();
    EditMenu->addAction(PrintAct);

    FormatMenu = menuBar()->addMenu(tr("格式(O)"));
    FormatMenu->addAction(NewLineAct);
    LookMenu = menuBar()->addMenu(tr("查看(L)"));
    AboutMenu = menuBar()->addMenu(tr("帮助(A)"));
    AboutMenu->addAction(AboutAct);
}

//建立工具栏
void RHZNotepad::CreateToolBars()
{
    //添加文件工具栏
    fileToolbar = addToolBar("fileToolBar");
    fileToolbar->addAction(newAct);
    fileToolbar->addAction(OpenAct);
    fileToolbar->addAction(SaveAct);

    //添加编辑工具栏
    editToolbar = addToolBar("editToolbar");
    editToolbar->addAction(CutAct);
    editToolbar->addAction(CopyAct);
    editToolbar->addAction(PastAct);
    editToolbar->addAction(PrintAct);
    //设置工具栏停靠处
    editToolbar->setAllowedAreas(Qt::LeftToolBarArea |Qt::TopToolBarArea);

    //添加设置工具栏*************************************************************************/
    SetToolbar = addToolBar("SetToolBar");
    //初始化设置工具栏
    SetFontStyle();
    SetToolbar->addAction(SetPageColorAct);

    formatBar = addToolBar("textformatbar");
    SetTextFormat();


}

//设置字体样式
void RHZNotepad::SetFontStyle()
{
    QLabel *label1 = new QLabel(tr("字体："));
    fontBox = new QFontComboBox(SetToolbar);

       //过滤，只在下拉列表中显示某一类字体，默认为QFontComboBox::AllFonts所有字体
       /*以我目前的水平和我的实验，加与不加没啥区别！！！*/
    fontBox->setFontFilters(QFontComboBox::ScalableFonts);
    SetToolbar->addWidget(label1);
    SetToolbar->addWidget(fontBox);

    SetToolbar->addSeparator();
    SetToolbar->addSeparator();

               /*字号*/
    QLabel *label2 = new QLabel(tr("字号："));
    sizeBox = new QComboBox(SetToolbar);
    SetToolbar->addWidget(label2);
    SetToolbar->addWidget(sizeBox);

       //QFontDatabase:当前系统中所有可用的格式信息，主要是字体的字号大小
    QFontDatabase db;
       //standardSizes():返回可用的标准字号列表
    foreach (int size, db.standardSizes() )
    {
       sizeBox->addItem(QString::number(size));
       sizeBox->setCurrentIndex(sizeBox->findText(QString::number(11)));
    }
           /*增加分隔符*/
    SetToolbar->addSeparator();

       /*加粗、斜体、下画线、颜色*/
    boldBtn = new QToolButton ;
    boldBtn->setIcon(QIcon(":/bold.png"));
    boldBtn->setCheckable(true);//boldBtn->setChecked(true);以前写的就是这，但是有误
    SetToolbar->addWidget(boldBtn);

    italicBtn = new QToolButton(this);
    italicBtn->setIcon(QIcon(":/italic.png"));
    italicBtn->setCheckable(true);
    SetToolbar->addWidget(italicBtn);

    underBtn = new QToolButton(this) ;
    underBtn->setIcon(QIcon(":/underline.png"));
    underBtn->setCheckable(true);
    SetToolbar->addWidget(underBtn);

    SetToolbar->addSeparator();
    colorBtn = new QToolButton(this);
    colorBtn->setIcon(QIcon(":/color.png"));
    SetToolbar->addWidget(colorBtn);

    connect(fontBox,SIGNAL(activated(QString)), this,SLOT(slotFont(QString)));
    connect(sizeBox,SIGNAL(activated(QString)), this,SLOT(slotSize(QString)));
    connect(boldBtn,SIGNAL(clicked()), this , SLOT(slotBold()));
    connect(italicBtn,SIGNAL(clicked()),this,SLOT(slotItalic()));
    connect(underBtn,SIGNAL(clicked()),this,SLOT(slotUnder()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(slotColor()));
}

//建立状态栏
void RHZNotepad::CreateStatusBar()
{
    statusBar()->showMessage(tr("就绪..."));
}

//添加事件
void RHZNotepad::CreateActions()
{

    newAct = new QAction(QIcon(":/new.png"),tr("新建"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("新建"));
    connect(newAct,SIGNAL(triggered()),this,SLOT(newFile()));

    OpenAct = new QAction(QIcon(":/open.png"),tr("打开"),this);
    OpenAct->setShortcuts(QKeySequence::Open);
    OpenAct->setStatusTip(tr("打开"));
    connect(OpenAct,SIGNAL(triggered()),this,SLOT(OpenFile()));

    SaveAct = new QAction(QIcon(":/save.png"),tr("保存"),this);
    SaveAct->setShortcuts(QKeySequence::Save);
    SaveAct->setStatusTip(tr("保存"));
    connect(SaveAct,SIGNAL(triggered()),this,SLOT(SaveFile()));

    SaveAsAct = new QAction(tr("另存为..."),this);
    SaveAsAct->setShortcuts(QKeySequence::SaveAs);
    SaveAsAct->setStatusTip(tr("另存为..."));
    connect(SaveAsAct,SIGNAL(triggered()),this,SLOT(SaveAsFile()));

    ExitAct = new QAction(tr("退出"),this);
    ExitAct->setStatusTip(tr("退出"));
    connect(ExitAct,SIGNAL(triggered()),this,SLOT(close()));



    CutAct = new QAction(QIcon(":/cut.png"),tr("剪切"),this);
    CutAct->setShortcuts(QKeySequence::Cut);
    CutAct->setStatusTip(tr("剪切"));
    connect(CutAct,SIGNAL(triggered()),textArea,SLOT(cut()));

    CopyAct = new QAction(QIcon(":/copy.png"),tr("复制"),this);
    CopyAct->setShortcuts(QKeySequence::Copy);
    CopyAct->setStatusTip(tr("复制"));
    connect(CopyAct,SIGNAL(triggered()),textArea,SLOT(copy()));

    PastAct = new QAction(QIcon(":/paste.png"),tr("粘贴"),this);
    PastAct->setShortcuts(QKeySequence::Paste);
    PastAct->setStatusTip(tr("粘帖"));
    connect(PastAct,SIGNAL(triggered()),textArea,SLOT(paste()));

    PrintAct = new QAction(QIcon(":/print.png"),tr("打印"),this);
    PrintAct->setShortcut(tr("Ctrl+P"));
    PrintAct->setStatusTip(tr("打印"));
    connect(PrintAct,SIGNAL(triggered()),this,SLOT(slotPrint()));

    AboutAct = new QAction(tr("关于"),this);
    connect(AboutAct,SIGNAL(triggered()),this,SLOT(AboutProcess()));

    SetPageColorAct = new QAction(QIcon(":/PagColor.ico"),tr("页面颜色"),this);
    SetPageColorAct->setStatusTip(tr("页面颜色"));
    connect(SetPageColorAct,SIGNAL(triggered()),this,SLOT(slotSetTextBackground()));

    //自动换行
    NewLineAct = new QAction(tr("自动换行"),this);
    NewLineAct->setCheckable(true);
    connect(NewLineAct,SIGNAL(triggered()),this,SLOT(slotIsLineWarp()));
}

//新建
void RHZNotepad::newFile()
{
    //qDebug()<<tr("新建文件");
    if( isModify() )
    {
        textArea->clear();
        setCurrentFileName("");
    }
}

//打开
void RHZNotepad::OpenFile()
{
    //qDebug()<<tr("打开文件");
    QString fileName = QFileDialog::getOpenFileName(this,tr("提示"),"",
                                                    tr("lsy file(*.lsy);;rhz file(*.rhz)"));
    if(fileName.isEmpty())
       {
           QMessageBox::warning(this,tr("提示"),tr("打开文件失败!"));
           return ;
       }else
       {

           QFile file(fileName);
           if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
           {
               QMessageBox::about(this,tr("提示"),tr("读取文件失败！"));
               return ;
           }
           QTextStream in(&file);
           QString textData;
           textData = in.readAll();//读入数据流
           //textArea->setPlainText(textData);
           textArea->document()->setHtml(textData);
           file.close();
           SourceFileName = fileName;//这句不写，影响到文件的保存
           setCurrentFileName(SourceFileName);
       }
}

//保存
void RHZNotepad::SaveFile()
{
   // qDebug()<<tr("保存文件");
    QFile file(SourceFileName);
    if( SourceFileName.isEmpty() )
    {
        //调用另存为
        SaveAsFile();
        return ;
    }

    if( !file.open(QIODevice::WriteOnly) )
    {
        QMessageBox::about(this,tr("提示"),tr("读取文件失败!"));
        return ;
    }

    QTextStream out(&file);
    out<<textArea->document()->toHtml();
    file.close();
    setCurrentFileName(SourceFileName);
    statusBar()->showMessage(tr("保存文件成功"));
}

//另存为...
void RHZNotepad::SaveAsFile()
{
   // qDebug()<<tr("另存为...");
    QString initPath = QDir::currentPath() + "/lsyairhz.lsy";
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save file"),initPath,
                                                       tr("lsy file(*.lsy);;rhz file(*.rhz)"));
    if(fileName.isEmpty())
    {
       QMessageBox::warning(this,tr("提示"),tr("保存文件失败!"));
       return ;
    }else
    {
       QFile file(fileName);
       if(!file.open(QIODevice::WriteOnly))
       {
          QMessageBox::warning(this,tr("提示"),tr("写入文件失败!"));
          return;
       }
       QTextStream out(&file);
       out<<textArea->document()->toHtml();
       file.close();
       QMessageBox::about(this,tr("提示"),tr("保存成功"));
    }
    setCurrentFileName(fileName);

}

//关于程序
void RHZNotepad::AboutProcess()
{
    QMessageBox::about(this,tr("关于..."),
                       tr("爱心记事本\n制作：奇世雅一"));
}

//打印文本
void RHZNotepad::slotPrint()
{
    QPrinter printer;
    QPrintDialog printDlg(&printer,this);

    if(printDlg.exec())
    {
        QTextDocument *doc = textArea->document();
        doc->print(&printer);
    }
}

//提示文本是否被修改
bool RHZNotepad::isModify()
{
    QMessageBox::StandardButton ret;

    if( textArea->document()->isModified() )
    {
        ret = QMessageBox::warning(this,tr("提示"),
                                   tr("该文本已被修改，是否要保存？"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(ret == QMessageBox::Save)
        {
            //调用保存函数
            SaveFile();
        }else if(ret == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

//设置文本标题
void RHZNotepad::setCurrentFileName(const QString &curName)
{
    //qDebug()<<tr("设置当前文件名字");
    SourceFileName = curName;
    textArea->document()->setModified(false);
    setWindowModified(false);

    QString showName = SourceFileName;
    if(SourceFileName.isEmpty())
    {
        showName = "LSYAIRHZ.lsy";
    }
    setWindowFilePath(showName);
}

//去除文件路径，保留文件名
QString RHZNotepad::GetFileName(const QString &filePathName)
{
    return QFileInfo(filePathName).fileName();
}

//判断文档是否改变
void RHZNotepad::TextAreaWasModified()
{
    setWindowModified(textArea->document()->isModified());
}

//关闭窗口事件
void RHZNotepad::closeEvent(QCloseEvent *event)
{
   // qDebug()<<tr("关闭窗口");
    bool flagEdit =  textArea->document()->isModified();
    QMessageBox::StandardButton ret ;

    if( flagEdit )
    {
        ret = QMessageBox::warning(this,tr("提示"),
                                   tr("此文档已经改变.\n"
                                      "您是否想保存改变后的文档?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    }
    if(ret == QMessageBox::Save || ret == QMessageBox::Cancel)
    {
        event->ignore();
    }
    //写入位置记录
    WriteSetting();
}

//读取位置
void RHZNotepad::ReadSetting()
{
    QSettings settings("LSY","TEXT EDIT");

    QPoint pos = settings.value("pos",QPoint(521,521)).toPoint();
    QSize  size = settings.value("size",QSize(521,521)).toSize();

    resize(size);//调整窗体大小
    move(pos);//把窗体移动到pos位置
}
//记录位置
void RHZNotepad::WriteSetting()
{
    QSettings settings("LSY","TEXT EDIT");
    settings.setValue("pos",pos());
    settings.setValue("size",size());
}

//设置页面背景颜色
void RHZNotepad::slotSetTextBackground()
{
   // qDebug()<<tr("设置背景颜色");
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())//检测颜色是否有效
    {
        QPalette palette = textArea->palette();
        palette.setColor(QPalette::Base,color);
        textArea->setPalette(palette);

    }
}

//是否自动换行
void RHZNotepad::slotIsLineWarp()
{
   // qDebug()<<tr("是否自动换行？");

    if(NewLineAct->isCheckable())
    {
        if(NewLineAct->isChecked())
        {
           // qDebug()<<tr("实现自动换行");
            textArea->setLineWrapMode(QTextEdit::WidgetWidth);
        }else
        {
           // qDebug()<<tr("取消自动换行");
            textArea->setLineWrapMode(QTextEdit::NoWrap);
        }
    }
}

//获取光标选择字符
void RHZNotepad::mergeFormat(QTextCharFormat format)
{
   // qDebug()<<tr("获取选择字符");
    /*QTextCursor:用来表示编辑文本框中的光标
    所有对于QTextDocument进行的修改都通过QTextCursor类来完成，mergeFormat()函数的作用
    即利用QTextCursor类把所有新的格式应用到光标选择区内的字符上，每个格式设置槽函数最后都需要
    调用此函数来应用更新。
    关于获取编辑框中的光标，若光标没有高亮选择区则把光标所在处的词作为选区，由前后空格或“，”、“.”
    等标点符号区分词。调用QTextCursor的mergeCharFormat()函数把参数format所表示的格式应用到
    光标所在处的字符上，最后调用QTextEdit的mergeCurrentCharFormat()函数把格式应用到选区内的所有
    字符上。

    QTextCursor::Document	        3	Selects the entire document.
    QTextCursor::BlockUnderCursor	2	Selects the block of text under the cursor.
    QTextCursor::LineUnderCursor	1	Selects the line of text under the cursor.
    QTextCursor::WordUnderCursor	0	Selects the word under the cursor. If the
                                           cursor is not positioned within a string of
                                           selectable characters, no text is selected.
     */

    QTextCursor cursor = textArea->textCursor();
    if( !cursor.hasSelection() )
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    textArea->mergeCurrentCharFormat(format);
}


//字体大小
void RHZNotepad::slotSize(QString num)
{
   // qDebug()<<tr("设置字体大小");
    QTextCharFormat fmt;
    fmt.setFontPointSize(num.toFloat());
    mergeFormat(fmt);
}

//设置字体
void RHZNotepad::slotFont(QString f)
{
  //  qDebug()<<tr("设置字体");
    QTextCharFormat fmt;
    fmt.setFontFamily(f);//选择字体名称设置给QTextCharFormat对象。
    mergeFormat(fmt);//把新的格式应用到光标选择区域内的字符
}

//加粗字体
void RHZNotepad::slotBold()
{
  //  qDebug()<<tr("设置粗体");
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
void RHZNotepad::slotItalic()
{
 //   qDebug()<<tr("设置倾斜");
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    mergeFormat(fmt);

}

void RHZNotepad::slotUnder()
{
  //  qDebug()<<tr("添加下划线");
    QTextCharFormat fmt;
    fmt.setFontUnderline(underBtn->isChecked());
    mergeFormat(fmt);
}

void RHZNotepad::slotColor()
{
//    qDebug()<<tr("设置字体颜色");
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        mergeFormat(fmt);
    }
}
//当前格式改变
void RHZNotepad::slotCurrentFormatChanged(const QTextCharFormat &fmt)
{
  //  qDebug()<<"6";
    fontBox->setCurrentIndex(fontBox->findText(fmt.fontFamily()));
    sizeBox->setCurrentIndex(sizeBox->findText(QString::number(fmt.FontPointSize)));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underBtn->setChecked(fmt.fontUnderline());
}

//设置文本格式
void RHZNotepad::SetTextFormat()
{
    //排序
    label = new QLabel(tr("排序："));
    listBox = new QComboBox(formatBar);
    //排序风格
    listBox->addItem(tr("标准"));
    listBox->addItem(tr("小圆点"));
    listBox->addItem(tr("小圆圈"));
    listBox->addItem(tr("四方块"));
    listBox->addItem(tr("数字"));
    listBox->addItem(tr("小写字母"));
    listBox->addItem(tr("大写字母"));
    formatBar->addWidget(label);
    formatBar->addWidget(listBox);

        //增加一个分隔符
    formatBar->addSeparator();

        //添加一个动作集合QActionGroup
    QActionGroup *actGrp = new QActionGroup(formatBar);

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



        //前进
    redoAction = new QAction(QIcon(":/redo"),tr("恢复"),this);
        //后退
    undoAction = new QAction(QIcon(":/undo"),tr("撤销"),this);

    //添加动作集合
    formatBar->addActions(actGrp->actions());
    formatBar->addAction(redoAction);
    formatBar->addAction(undoAction);

        //建立信号槽
    connect(listBox,SIGNAL(activated(int)),this,SLOT(slotList(int)));
    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(slotAlignment(QAction*)));

    connect(redoAction,SIGNAL(triggered()),textArea,SLOT(redo()));
    connect(undoAction,SIGNAL(triggered()),textArea,SLOT(undo()));

    connect(textArea->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(textArea->document(),SIGNAL(undoAvailable(bool)),undoAction,SLOT(setEnabled(bool)));

    connect(textArea,SIGNAL(cursorPositionChanged()),this,SLOT(slotCursorPositionChanged()));
}

//设置文本对齐方式
void RHZNotepad::slotAlignment(QAction *act)
{
  //  qDebug()<<"slotAlignment";
    if( !NewLineAct->isChecked() )
    {
        QMessageBox::warning(this,tr("提示"),
                             tr("请您把本程序默认的不自动换行功能取消后\n再来设置文本的对齐方式！"));
        return ;
    }

    if( act == leftAction )
        textArea->setAlignment(Qt::AlignLeft);

    if( act == centerAction )
        textArea->setAlignment(Qt::AlignCenter);

    if( act == justifyAction )
        textArea->setAlignment(Qt::AlignJustify);

    if( act == rightAction )
    {
        qDebug()<<tr("右");
        textArea->setAlignment(Qt::AlignRight);
    }
    update();

}

//设置相应对齐方式为按下状态。
void RHZNotepad::slotCursorPositionChanged()
{
  //  qDebug()<<"slotCursorPositionChanged";
    /*
       alignment()函数获得光标当前位置所处段落的对齐方式，设置相应对齐方式为按下状态。
    */
    if(textArea->alignment() == Qt::AlignLeft)
        leftAction->setChecked(true);

    if(textArea->alignment() == Qt::AlignCenter )
        centerAction->setChecked(true);

    if(textArea->alignment() == Qt::AlignJustify )
        justifyAction->setChecked(true);

    if(textArea->alignment() == Qt::AlignRight )
        rightAction->setChecked(true);

}

//设置排序方式
void RHZNotepad::slotList(int index)
{
   // qDebug()<<"slotList";
    QTextCursor cursor = textArea->textCursor();
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
