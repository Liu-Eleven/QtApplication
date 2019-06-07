#ifndef TEXTALIGN_H
#define TEXTALIGN_H

#include <QtGui>

class TextAlign : public QMainWindow
{
    Q_OBJECT

public:
    TextAlign(QWidget *parent = 0);
    ~TextAlign();
private slots:
    void slotAlignment(QAction *);
    void slotList(int);
    void slotCursorPositionChanged();

private:
    QTextEdit *text;
    QLabel *label;
    QComboBox *listBox;

    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;
    QAction *redoAction;
    QAction *undoAction;

};

#endif // TEXTALIGN_H
