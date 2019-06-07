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
//��ʼ���������
void RHZNotepad::InitializeInterface()
{
    textArea = new QTextEdit(this);
    textArea->setAcceptRichText(true);
    textArea->setTabStopWidth(40);

    //textArea->setStyleSheet("background-image::url(:/BackGround.jpg)");
    //textArea->setHtml("<body background= ./BackGround.jpg/></body>");

    //���û���ģʽΪ������
    textArea->setLineWrapMode(QTextEdit::NoWrap);
    //����ˮƽ�������ʹ�ֱ������
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

//�����˵���
void RHZNotepad::CreateMenus()
{
    //�ļ��˵�
    FileMenu = menuBar()->addMenu(tr("�ļ�(F)"));
    //��Ӷ���
    FileMenu->addAction(newAct);
    FileMenu->addAction(OpenAct);
    FileMenu->addAction(SaveAct);
    FileMenu->addAction(SaveAsAct);
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAct);

    EditMenu = menuBar()->addMenu(tr("�༭(E)"));
    EditMenu->addAction(CutAct);
    EditMenu->addAction(CopyAct);
    EditMenu->addAction(PastAct);
    EditMenu->addSeparator();
    EditMenu->addAction(PrintAct);

    FormatMenu = menuBar()->addMenu(tr("��ʽ(O)"));
    FormatMenu->addAction(NewLineAct);
    LookMenu = menuBar()->addMenu(tr("�鿴(L)"));
    AboutMenu = menuBar()->addMenu(tr("����(A)"));
    AboutMenu->addAction(AboutAct);
}

//����������
void RHZNotepad::CreateToolBars()
{
    //����ļ�������
    fileToolbar = addToolBar("fileToolBar");
    fileToolbar->addAction(newAct);
    fileToolbar->addAction(OpenAct);
    fileToolbar->addAction(SaveAct);

    //��ӱ༭������
    editToolbar = addToolBar("editToolbar");
    editToolbar->addAction(CutAct);
    editToolbar->addAction(CopyAct);
    editToolbar->addAction(PastAct);
    editToolbar->addAction(PrintAct);
    //���ù�����ͣ����
    editToolbar->setAllowedAreas(Qt::LeftToolBarArea |Qt::TopToolBarArea);

    //������ù�����*************************************************************************/
    SetToolbar = addToolBar("SetToolBar");
    //��ʼ�����ù�����
    SetFontStyle();
    SetToolbar->addAction(SetPageColorAct);

    formatBar = addToolBar("textformatbar");
    SetTextFormat();


}

//����������ʽ
void RHZNotepad::SetFontStyle()
{
    QLabel *label1 = new QLabel(tr("���壺"));
    fontBox = new QFontComboBox(SetToolbar);

       //���ˣ�ֻ�������б�����ʾĳһ�����壬Ĭ��ΪQFontComboBox::AllFonts��������
       /*����Ŀǰ��ˮƽ���ҵ�ʵ�飬���벻��ûɶ���𣡣���*/
    fontBox->setFontFilters(QFontComboBox::ScalableFonts);
    SetToolbar->addWidget(label1);
    SetToolbar->addWidget(fontBox);

    SetToolbar->addSeparator();
    SetToolbar->addSeparator();

               /*�ֺ�*/
    QLabel *label2 = new QLabel(tr("�ֺţ�"));
    sizeBox = new QComboBox(SetToolbar);
    SetToolbar->addWidget(label2);
    SetToolbar->addWidget(sizeBox);

       //QFontDatabase:��ǰϵͳ�����п��õĸ�ʽ��Ϣ����Ҫ��������ֺŴ�С
    QFontDatabase db;
       //standardSizes():���ؿ��õı�׼�ֺ��б�
    foreach (int size, db.standardSizes() )
    {
       sizeBox->addItem(QString::number(size));
       sizeBox->setCurrentIndex(sizeBox->findText(QString::number(11)));
    }
           /*���ӷָ���*/
    SetToolbar->addSeparator();

       /*�Ӵ֡�б�塢�»��ߡ���ɫ*/
    boldBtn = new QToolButton ;
    boldBtn->setIcon(QIcon(":/bold.png"));
    boldBtn->setCheckable(true);//boldBtn->setChecked(true);��ǰд�ľ����⣬��������
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

//����״̬��
void RHZNotepad::CreateStatusBar()
{
    statusBar()->showMessage(tr("����..."));
}

//����¼�
void RHZNotepad::CreateActions()
{

    newAct = new QAction(QIcon(":/new.png"),tr("�½�"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("�½�"));
    connect(newAct,SIGNAL(triggered()),this,SLOT(newFile()));

    OpenAct = new QAction(QIcon(":/open.png"),tr("��"),this);
    OpenAct->setShortcuts(QKeySequence::Open);
    OpenAct->setStatusTip(tr("��"));
    connect(OpenAct,SIGNAL(triggered()),this,SLOT(OpenFile()));

    SaveAct = new QAction(QIcon(":/save.png"),tr("����"),this);
    SaveAct->setShortcuts(QKeySequence::Save);
    SaveAct->setStatusTip(tr("����"));
    connect(SaveAct,SIGNAL(triggered()),this,SLOT(SaveFile()));

    SaveAsAct = new QAction(tr("���Ϊ..."),this);
    SaveAsAct->setShortcuts(QKeySequence::SaveAs);
    SaveAsAct->setStatusTip(tr("���Ϊ..."));
    connect(SaveAsAct,SIGNAL(triggered()),this,SLOT(SaveAsFile()));

    ExitAct = new QAction(tr("�˳�"),this);
    ExitAct->setStatusTip(tr("�˳�"));
    connect(ExitAct,SIGNAL(triggered()),this,SLOT(close()));



    CutAct = new QAction(QIcon(":/cut.png"),tr("����"),this);
    CutAct->setShortcuts(QKeySequence::Cut);
    CutAct->setStatusTip(tr("����"));
    connect(CutAct,SIGNAL(triggered()),textArea,SLOT(cut()));

    CopyAct = new QAction(QIcon(":/copy.png"),tr("����"),this);
    CopyAct->setShortcuts(QKeySequence::Copy);
    CopyAct->setStatusTip(tr("����"));
    connect(CopyAct,SIGNAL(triggered()),textArea,SLOT(copy()));

    PastAct = new QAction(QIcon(":/paste.png"),tr("ճ��"),this);
    PastAct->setShortcuts(QKeySequence::Paste);
    PastAct->setStatusTip(tr("ճ��"));
    connect(PastAct,SIGNAL(triggered()),textArea,SLOT(paste()));

    PrintAct = new QAction(QIcon(":/print.png"),tr("��ӡ"),this);
    PrintAct->setShortcut(tr("Ctrl+P"));
    PrintAct->setStatusTip(tr("��ӡ"));
    connect(PrintAct,SIGNAL(triggered()),this,SLOT(slotPrint()));

    AboutAct = new QAction(tr("����"),this);
    connect(AboutAct,SIGNAL(triggered()),this,SLOT(AboutProcess()));

    SetPageColorAct = new QAction(QIcon(":/PagColor.ico"),tr("ҳ����ɫ"),this);
    SetPageColorAct->setStatusTip(tr("ҳ����ɫ"));
    connect(SetPageColorAct,SIGNAL(triggered()),this,SLOT(slotSetTextBackground()));

    //�Զ�����
    NewLineAct = new QAction(tr("�Զ�����"),this);
    NewLineAct->setCheckable(true);
    connect(NewLineAct,SIGNAL(triggered()),this,SLOT(slotIsLineWarp()));
}

//�½�
void RHZNotepad::newFile()
{
    //qDebug()<<tr("�½��ļ�");
    if( isModify() )
    {
        textArea->clear();
        setCurrentFileName("");
    }
}

//��
void RHZNotepad::OpenFile()
{
    //qDebug()<<tr("���ļ�");
    QString fileName = QFileDialog::getOpenFileName(this,tr("��ʾ"),"",
                                                    tr("lsy file(*.lsy);;rhz file(*.rhz)"));
    if(fileName.isEmpty())
       {
           QMessageBox::warning(this,tr("��ʾ"),tr("���ļ�ʧ��!"));
           return ;
       }else
       {

           QFile file(fileName);
           if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
           {
               QMessageBox::about(this,tr("��ʾ"),tr("��ȡ�ļ�ʧ�ܣ�"));
               return ;
           }
           QTextStream in(&file);
           QString textData;
           textData = in.readAll();//����������
           //textArea->setPlainText(textData);
           textArea->document()->setHtml(textData);
           file.close();
           SourceFileName = fileName;//��䲻д��Ӱ�쵽�ļ��ı���
           setCurrentFileName(SourceFileName);
       }
}

//����
void RHZNotepad::SaveFile()
{
   // qDebug()<<tr("�����ļ�");
    QFile file(SourceFileName);
    if( SourceFileName.isEmpty() )
    {
        //�������Ϊ
        SaveAsFile();
        return ;
    }

    if( !file.open(QIODevice::WriteOnly) )
    {
        QMessageBox::about(this,tr("��ʾ"),tr("��ȡ�ļ�ʧ��!"));
        return ;
    }

    QTextStream out(&file);
    out<<textArea->document()->toHtml();
    file.close();
    setCurrentFileName(SourceFileName);
    statusBar()->showMessage(tr("�����ļ��ɹ�"));
}

//���Ϊ...
void RHZNotepad::SaveAsFile()
{
   // qDebug()<<tr("���Ϊ...");
    QString initPath = QDir::currentPath() + "/lsyairhz.lsy";
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save file"),initPath,
                                                       tr("lsy file(*.lsy);;rhz file(*.rhz)"));
    if(fileName.isEmpty())
    {
       QMessageBox::warning(this,tr("��ʾ"),tr("�����ļ�ʧ��!"));
       return ;
    }else
    {
       QFile file(fileName);
       if(!file.open(QIODevice::WriteOnly))
       {
          QMessageBox::warning(this,tr("��ʾ"),tr("д���ļ�ʧ��!"));
          return;
       }
       QTextStream out(&file);
       out<<textArea->document()->toHtml();
       file.close();
       QMessageBox::about(this,tr("��ʾ"),tr("����ɹ�"));
    }
    setCurrentFileName(fileName);

}

//���ڳ���
void RHZNotepad::AboutProcess()
{
    QMessageBox::about(this,tr("����..."),
                       tr("���ļ��±�\n������������һ"));
}

//��ӡ�ı�
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

//��ʾ�ı��Ƿ��޸�
bool RHZNotepad::isModify()
{
    QMessageBox::StandardButton ret;

    if( textArea->document()->isModified() )
    {
        ret = QMessageBox::warning(this,tr("��ʾ"),
                                   tr("���ı��ѱ��޸ģ��Ƿ�Ҫ���棿"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(ret == QMessageBox::Save)
        {
            //���ñ��溯��
            SaveFile();
        }else if(ret == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

//�����ı�����
void RHZNotepad::setCurrentFileName(const QString &curName)
{
    //qDebug()<<tr("���õ�ǰ�ļ�����");
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

//ȥ���ļ�·���������ļ���
QString RHZNotepad::GetFileName(const QString &filePathName)
{
    return QFileInfo(filePathName).fileName();
}

//�ж��ĵ��Ƿ�ı�
void RHZNotepad::TextAreaWasModified()
{
    setWindowModified(textArea->document()->isModified());
}

//�رմ����¼�
void RHZNotepad::closeEvent(QCloseEvent *event)
{
   // qDebug()<<tr("�رմ���");
    bool flagEdit =  textArea->document()->isModified();
    QMessageBox::StandardButton ret ;

    if( flagEdit )
    {
        ret = QMessageBox::warning(this,tr("��ʾ"),
                                   tr("���ĵ��Ѿ��ı�.\n"
                                      "���Ƿ��뱣��ı����ĵ�?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    }
    if(ret == QMessageBox::Save || ret == QMessageBox::Cancel)
    {
        event->ignore();
    }
    //д��λ�ü�¼
    WriteSetting();
}

//��ȡλ��
void RHZNotepad::ReadSetting()
{
    QSettings settings("LSY","TEXT EDIT");

    QPoint pos = settings.value("pos",QPoint(521,521)).toPoint();
    QSize  size = settings.value("size",QSize(521,521)).toSize();

    resize(size);//���������С
    move(pos);//�Ѵ����ƶ���posλ��
}
//��¼λ��
void RHZNotepad::WriteSetting()
{
    QSettings settings("LSY","TEXT EDIT");
    settings.setValue("pos",pos());
    settings.setValue("size",size());
}

//����ҳ�汳����ɫ
void RHZNotepad::slotSetTextBackground()
{
   // qDebug()<<tr("���ñ�����ɫ");
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())//�����ɫ�Ƿ���Ч
    {
        QPalette palette = textArea->palette();
        palette.setColor(QPalette::Base,color);
        textArea->setPalette(palette);

    }
}

//�Ƿ��Զ�����
void RHZNotepad::slotIsLineWarp()
{
   // qDebug()<<tr("�Ƿ��Զ����У�");

    if(NewLineAct->isCheckable())
    {
        if(NewLineAct->isChecked())
        {
           // qDebug()<<tr("ʵ���Զ�����");
            textArea->setLineWrapMode(QTextEdit::WidgetWidth);
        }else
        {
           // qDebug()<<tr("ȡ���Զ�����");
            textArea->setLineWrapMode(QTextEdit::NoWrap);
        }
    }
}

//��ȡ���ѡ���ַ�
void RHZNotepad::mergeFormat(QTextCharFormat format)
{
   // qDebug()<<tr("��ȡѡ���ַ�");
    /*QTextCursor:������ʾ�༭�ı����еĹ��
    ���ж���QTextDocument���е��޸Ķ�ͨ��QTextCursor������ɣ�mergeFormat()����������
    ������QTextCursor��������µĸ�ʽӦ�õ����ѡ�����ڵ��ַ��ϣ�ÿ����ʽ���òۺ��������Ҫ
    ���ô˺�����Ӧ�ø��¡�
    ���ڻ�ȡ�༭���еĹ�꣬�����û�и���ѡ������ѹ�����ڴ��Ĵ���Ϊѡ������ǰ��ո�򡰣�������.��
    �ȱ��������ִʡ�����QTextCursor��mergeCharFormat()�����Ѳ���format����ʾ�ĸ�ʽӦ�õ�
    ������ڴ����ַ��ϣ�������QTextEdit��mergeCurrentCharFormat()�����Ѹ�ʽӦ�õ�ѡ���ڵ�����
    �ַ��ϡ�

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


//�����С
void RHZNotepad::slotSize(QString num)
{
   // qDebug()<<tr("���������С");
    QTextCharFormat fmt;
    fmt.setFontPointSize(num.toFloat());
    mergeFormat(fmt);
}

//��������
void RHZNotepad::slotFont(QString f)
{
  //  qDebug()<<tr("��������");
    QTextCharFormat fmt;
    fmt.setFontFamily(f);//ѡ�������������ø�QTextCharFormat����
    mergeFormat(fmt);//���µĸ�ʽӦ�õ����ѡ�������ڵ��ַ�
}

//�Ӵ�����
void RHZNotepad::slotBold()
{
  //  qDebug()<<tr("���ô���");
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
void RHZNotepad::slotItalic()
{
 //   qDebug()<<tr("������б");
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    mergeFormat(fmt);

}

void RHZNotepad::slotUnder()
{
  //  qDebug()<<tr("����»���");
    QTextCharFormat fmt;
    fmt.setFontUnderline(underBtn->isChecked());
    mergeFormat(fmt);
}

void RHZNotepad::slotColor()
{
//    qDebug()<<tr("����������ɫ");
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        mergeFormat(fmt);
    }
}
//��ǰ��ʽ�ı�
void RHZNotepad::slotCurrentFormatChanged(const QTextCharFormat &fmt)
{
  //  qDebug()<<"6";
    fontBox->setCurrentIndex(fontBox->findText(fmt.fontFamily()));
    sizeBox->setCurrentIndex(sizeBox->findText(QString::number(fmt.FontPointSize)));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underBtn->setChecked(fmt.fontUnderline());
}

//�����ı���ʽ
void RHZNotepad::SetTextFormat()
{
    //����
    label = new QLabel(tr("����"));
    listBox = new QComboBox(formatBar);
    //������
    listBox->addItem(tr("��׼"));
    listBox->addItem(tr("СԲ��"));
    listBox->addItem(tr("СԲȦ"));
    listBox->addItem(tr("�ķ���"));
    listBox->addItem(tr("����"));
    listBox->addItem(tr("Сд��ĸ"));
    listBox->addItem(tr("��д��ĸ"));
    formatBar->addWidget(label);
    formatBar->addWidget(listBox);

        //����һ���ָ���
    formatBar->addSeparator();

        //���һ����������QActionGroup
    QActionGroup *actGrp = new QActionGroup(formatBar);

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



        //ǰ��
    redoAction = new QAction(QIcon(":/redo"),tr("�ָ�"),this);
        //����
    undoAction = new QAction(QIcon(":/undo"),tr("����"),this);

    //��Ӷ�������
    formatBar->addActions(actGrp->actions());
    formatBar->addAction(redoAction);
    formatBar->addAction(undoAction);

        //�����źŲ�
    connect(listBox,SIGNAL(activated(int)),this,SLOT(slotList(int)));
    connect(actGrp,SIGNAL(triggered(QAction*)),this,SLOT(slotAlignment(QAction*)));

    connect(redoAction,SIGNAL(triggered()),textArea,SLOT(redo()));
    connect(undoAction,SIGNAL(triggered()),textArea,SLOT(undo()));

    connect(textArea->document(),SIGNAL(redoAvailable(bool)),redoAction,SLOT(setEnabled(bool)));
    connect(textArea->document(),SIGNAL(undoAvailable(bool)),undoAction,SLOT(setEnabled(bool)));

    connect(textArea,SIGNAL(cursorPositionChanged()),this,SLOT(slotCursorPositionChanged()));
}

//�����ı����뷽ʽ
void RHZNotepad::slotAlignment(QAction *act)
{
  //  qDebug()<<"slotAlignment";
    if( !NewLineAct->isChecked() )
    {
        QMessageBox::warning(this,tr("��ʾ"),
                             tr("�����ѱ�����Ĭ�ϵĲ��Զ����й���ȡ����\n���������ı��Ķ��뷽ʽ��"));
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
        qDebug()<<tr("��");
        textArea->setAlignment(Qt::AlignRight);
    }
    update();

}

//������Ӧ���뷽ʽΪ����״̬��
void RHZNotepad::slotCursorPositionChanged()
{
  //  qDebug()<<"slotCursorPositionChanged";
    /*
       alignment()������ù�굱ǰλ����������Ķ��뷽ʽ��������Ӧ���뷽ʽΪ����״̬��
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

//��������ʽ
void RHZNotepad::slotList(int index)
{
   // qDebug()<<"slotList";
    QTextCursor cursor = textArea->textCursor();
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
