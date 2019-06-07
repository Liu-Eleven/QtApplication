#ifndef SETFONT_H
#define SETFONT_H

#include <QtGui>

class MySetFont : public QMainWindow
{
    Q_OBJECT

public:
    MySetFont(QWidget *parent = 0);
    ~MySetFont();

private slots:
    void slotFont(QString );
    void slotSize(QString );
    void slotItalic();
    void slotBold();
    void slotUnder();
    void slotColor();
    void slotCurrentFormatChanged(const QTextCharFormat &fmt);
private:
    QLabel *label1;
    QLabel *label2;

    QTextEdit *text;

    QFontComboBox *fontBox;
    QComboBox *sizeBox;
    QToolButton *boldBtn;
    QToolButton *underBtn;
    QToolButton *italicBtn;
    QToolButton *colorBtn;

    void mergeFormat(QTextCharFormat);


};

#endif // SETFONT_H
