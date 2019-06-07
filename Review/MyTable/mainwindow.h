#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mymodule.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void SelectIndex(QModelIndex,QModelIndex);
    void UserSelectChanged(const QItemSelection & , const QItemSelection & );

    void SaveToFile();
    void LoadFile();


private:
    Ui::MainWindow *ui;
    MyModule *myModule;
    QTableView *view;
};

#endif // MAINWINDOW_H
