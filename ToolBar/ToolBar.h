#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class ToolBar : public QMainWindow
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = 0);
    ~ToolBar();
private slots:
    void slotComboBox(QString );
    void slotSpinBox(QString );
private:
    QTextEdit *text;
    QSpinBox *spin;
    QComboBox *box;
};

#endif // MAINWINDOW_H
