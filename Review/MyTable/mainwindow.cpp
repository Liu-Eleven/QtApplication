#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myModule = new MyModule(this);

    LoadFile();

    view = new QTableView(this);
    view->setModel(myModule);
    this->setCentralWidget(view);

    //单选一项
    connect(view->selectionModel() , SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this , SLOT(SelectIndex(QModelIndex,QModelIndex)));

    //单选N项
    connect(view->selectionModel() , SIGNAL(selectionChanged(QItemSelection,QItemSelection)) ,
            this, SLOT(UserSelectChanged(QItemSelection,QItemSelection)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//选择一个单元
void MainWindow::SelectIndex(QModelIndex cur,QModelIndex pre)
{
   // qDebug()<<cur.row()+1 << cur.column()+1;
}

//选择多个单元
void MainWindow::UserSelectChanged(const QItemSelection & selected, const QItemSelection & deselected )
{

    QModelIndex index;

    for(int i=0; i<selected.count(); i++)
    {
        index = selected.indexes().at(i);
        qDebug()<< index.row()+1  << "  " <<  index.column()+1;
    }

}

void MainWindow::SaveToFile()
{
    QFile file("Student.ini");

    if (!file.open(QIODevice::ReadWrite))
        return;

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);
    int count =myModule->StuContainer.count();
    out << count;
    for(int i=0; i< count; i++)
    {
        out<<myModule->StuContainer[i].name;
        out<<myModule->StuContainer[i].age;
        out<<myModule->StuContainer[i].Sex;
        out<<myModule->StuContainer[i].phone;

    }
    file.close();
    qDebug()<<"Save";
}

void MainWindow::LoadFile()
{
    qDebug()<<"load file";
    //myModule->remo
    myModule->removeRow(0);
    myModule->removeRow(1);
    QFile file("Student.ini");

    if (!file.open(QIODevice::ReadWrite))
        return;

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_3);
    int count = 0;
    in >> count;
    Person person;
    for(int i=0; i< count; i++)
    {
        in >> person.name;
        in >> person.age;
        in >> person.Sex;
        in >> person.phone;
        myModule->StuContainer.push_back(person);
    }
    file.close();
}
