#ifndef RHZNOTEPAD_H
#define RHZNOTEPAD_H

#include <QtGui>

class RHZNotepad : public QMainWindow
{
    Q_OBJECT

public:
    RHZNotepad();
    ~RHZNotepad();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void newFile();
    void OpenFile();
    void SaveFile();
    void SaveAsFile();
    void slotPrint();
    void AboutProcess();

    void slotSetTextBackground();
    void slotIsLineWarp();
    void TextAreaWasModified();
    void slotCurrentFormatChanged(const QTextCharFormat &);

    //设置格式
    void slotFont(QString);
    void slotBold();
    void slotItalic();
    void slotUnder();
    void slotColor();

    void slotSize(QString );

    void slotAlignment(QAction *);
    void slotList(int);
    void slotCursorPositionChanged();
private:

    QMenu *FileMenu;
    QMenu *EditMenu;
    QMenu *FormatMenu;
    QMenu *LookMenu;
    QMenu *AboutMenu;

    QToolBar *fileToolbar;
    QToolBar *editToolbar;
    QToolBar *SetToolbar;
    QToolBar *formatBar;

    QTextEdit *textArea;

    QAction *newAct;
    QAction *OpenAct;
    QAction *SaveAct;
    QAction *SaveAsAct;
    QAction *ExitAct;

    QAction *CutAct;
    QAction *CopyAct;
    QAction *PastAct;

    //打印
    QAction *PrintAct;
    QAction *AboutAct;
    //设置背景颜色
    QAction *SetPageColorAct;
    //自动换行
    QAction *NewLineAct;
    //原路径
    QString SourceFileName;

    //定义设置文本
    QComboBox *sizeBox;

    QToolButton *boldBtn;
    QToolButton *underBtn;
    QToolButton *italicBtn;
    QToolButton *colorBtn;
    QFontComboBox *fontBox;

    //设置文本格式
    QLabel *label;
    QComboBox *listBox;

    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;
    QAction *redoAction;
    QAction *undoAction;


    //初始化程序界面
    void InitializeInterface();
    //建立菜单栏
    void CreateMenus();
    //建立工具栏
    void CreateToolBars();
    //建立状态栏
    void CreateStatusBar();
    //创建事件
    void CreateActions();
    //设置当前文件名
    void setCurrentFileName(const QString &);

    QString GetFileName(const QString &);
    //读取配置
    void ReadSetting();
    //写入文件位置记录
    void WriteSetting();
    //判断文本是否被改变
    bool isModify();
    //获取光标选择字符
    void mergeFormat(QTextCharFormat);

    //设置函数
    void SetFontStyle();
    void SetTextFormat();

};

#endif // RHZNOTEPAD_H
