#include "mymodule.h"

MyModule::MyModule(QObject *parent) :
    QAbstractTableModel(parent)
{
  /*  Person Per;
    Per.name = "����һ";
    Per.age = 21;
    Per.Sex = "��";
    Per.phone = "13597538930";
    this->StuContainer.push_back(Per);

    Per.name = "�κ���";
    Per.age = 20;
    Per.Sex = "Ů";
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

    //������ı�
    if(role == Qt::DisplayRole)
    {
        //��һ����ʾ��ʽ
        //return QString(QByteArray::number(row) + QByteArray::number(colum));
        //�ڶ�����ʾ��ʽ
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
        //�ı����䷽ʽ
        return Qt::AlignHCenter + Qt::AlignVCenter;
    }else if(role == Qt::DecorationRole)
    {
        //�����ͼ��
        if(row == 2 && colum == 4)
            return QIcon(":/Love.ico");
    }
    return QVariant();
}


QVariant MyModule::headerData(int section, Qt::Orientation orientation, int role) const
{
    /*
       ����������
       section :
       orientation :
       role :
    */
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch(section)
        {
        case 0:
            return "����";
        case 1:
            return "����";
        case 2:
            return "�Ա�";
        case 3:
            return "�绰";
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

