#ifndef MYMODULE_H
#define MYMODULE_H

#include <QtGui>
#include <QAbstractTableModel>

typedef struct Person{
    QString name;
    int age;
    QString Sex;
    QString phone;
} Person;

class MyModule :  public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModule(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    //返回是否可编辑
    Qt::ItemFlags flags(const QModelIndex &index) const;

    //公有模版变量
    QVector<Person> StuContainer;


};

#endif // MYMODULE_H
