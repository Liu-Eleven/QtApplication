#include "mymodule.h"

MyModule::MyModule(QObject *parent) :
    QAbstractTableModel(parent)
{
  /*  Person Per;
    Per.name = "刘世一";
    Per.age = 21;
    Per.Sex = "男";
    Per.phone = "13597538930";
    this->StuContainer.push_back(Per);

    Per.name = "任海征";
    Per.age = 20;
    Per.Sex = "女";
    Per.phone = "13597538930";
    this->StuContainer.push_back(Per);*/

}


int MyModule::rowCount(const QModelIndex &parent) const
{
    return StuContainer.count();
}
int MyModule::columnCount(const QModelIndex &parent) const
{
    return 4;
}


QVariant MyModule::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int colum = index.column();

    //如果是文本
    if(role == Qt::DisplayRole)
    {
        //第一种显示方式
        //return QString(QByteArray::number(row) + QByteArray::number(colum));
        //第二种显示方式
        switch(colum)
        {
        case 0:
            return StuContainer[row].name;
        case 1:
            return StuContainer[row].age;
        case 2:
            return StuContainer[row].Sex;
        case 3:
            return StuContainer[row].phone;
        }

    }else if(role == Qt::TextAlignmentRole)
    {
        //文本对其方式
        return Qt::AlignHCenter + Qt::AlignVCenter;
    }else if(role == Qt::DecorationRole)
    {
        //如果是图标
        if(row == 2 && colum == 4)
            return QIcon(":/Love.ico");
    }
    return QVariant();
}


QVariant MyModule::headerData(int section, Qt::Orientation orientation, int role) const
{
    /*
       参数解析：
       section :
       orientation :
       role :
    */
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
        case 0:
            return "姓名";
        case 1:
            return "年龄";
        case 2:
            return "性别";
        case 3:
            return "电话";
        }
    }

    if(orientation == Qt::Vertical && role == Qt::DecorationRole)
    {
        switch(section)
        {
        case 0:
            return QIcon(":/Love2.ico");
        case 1:
            return QIcon(":/Love3.ico");
        }

    }
    return QVariant();
}

bool MyModule::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if( !index.isValid() )
        return false;
    if(role != Qt::EditRole)
        return false;

    int row = index.row();
    int col = index.column();

    switch(col)
    {
    case 0:
        StuContainer[row].name = value.toString();
        break;
    case 1:
        StuContainer[row].age = value.toInt();
        break;
    case 2:
        StuContainer[row].Sex = value.toString();
    case 3:
        StuContainer[row].phone = value.toString();

    }


    return true;
}



Qt::ItemFlags MyModule::flags(const QModelIndex &) const
{
    return  Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

