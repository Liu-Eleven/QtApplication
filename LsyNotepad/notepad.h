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

    //���ø�ʽ
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

    //��ӡ
    QAction *PrintAct;
    QAction *AboutAct;
    //���ñ�����ɫ
    QAction *SetPageColorAct;
    //�Զ�����
    QAction *NewLineAct;
    //ԭ·��
    QString SourceFileName;

    //���������ı�
    QComboBox *sizeBox;

    QToolButton *boldBtn;
    QToolButton *underBtn;
    QToolButton *italicBtn;
    QToolButton *colorBtn;
    QFontComboBox *fontBox;

    //�����ı���ʽ
    QLabel *label;
    QComboBox *listBox;

    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;
    QAction *redoAction;
    QAction *undoAction;


    //��ʼ���������
    void InitializeInterface();
    //�����˵���
    void CreateMenus();
    //����������
    void CreateToolBars();
    //����״̬��
    void CreateStatusBar();
    //�����¼�
    void CreateActions();
    //���õ�ǰ�ļ���
    void setCurrentFileName(const QString &);

    QString GetFileName(const QString &);
    //��ȡ����
    void ReadSetting();
    //д���ļ�λ�ü�¼
    void WriteSetting();
    //�ж��ı��Ƿ񱻸ı�
    bool isModify();
    //��ȡ���ѡ���ַ�
    void mergeFormat(QTextCharFormat);

    //���ú���
    void SetFontStyle();
    void SetTextFormat();

};

#endif // RHZNOTEPAD_H
