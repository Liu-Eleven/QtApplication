#include "misdemo.h"
#include "ui_misdemo.h"

MISDemo::MISDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MISDemo)
{
    ui->setupUi(this);

    ui->FindStd->addItem(tr("   "));
    ui->FindStd->addItem(tr("姓名"));
    ui->FindStd->addItem(tr("性别"));
    ui->FindStd->addItem(tr("年龄"));
    ui->FindStd->addItem(tr("编号"));
    ui->FindStd->addItem(tr("地址"));

    SqlModel = new QSqlTableModel(this);
    //读取数据库中表的内容，setTable(tablename)为表名
    SqlModel->setTable("Student");
    //把表中的内容都选择出来
    SqlModel->select();

    SqlModel->setHeaderData(0,Qt::Horizontal,tr("姓名"));
    SqlModel->setHeaderData(1,Qt::Horizontal,tr("性别"));
    SqlModel->setHeaderData(2,Qt::Horizontal,tr("年龄"));
    SqlModel->setHeaderData(3,Qt::Horizontal,tr("编号"));
    SqlModel->setHeaderData(4,Qt::Horizontal,tr("地址"));
    //将SqlModel中的内容放到tableview中
    ui->tableView->setModel(SqlModel);

    update();
}

MISDemo::~MISDemo()
{
    delete ui;
}

void MISDemo::on_FindBtn_clicked()
{
    qDebug()<<FindStr;
    QString itemFiter(FindStr);
    itemFiter += "\"" +  ui->FindEdit->text() + "\"";
    qDebug()<<itemFiter;
    SqlModel->setFilter(itemFiter);
    SqlModel->select();

}

void MISDemo::on_DeleteBtn_clicked()
{
    qDebug()<<"DEL";
    int state = QMessageBox::warning(this,tr("删除"),tr("您确定要删除此项吗？"),
                                     QMessageBox::Yes | QMessageBox::No);
    if(state == QMessageBox::No)
    {
        return ;
    }else
    {
        //获取选中行
        int curRow = ui->tableView->currentIndex().row();
        SqlModel->removeRow(curRow);
    }
}

void MISDemo::on_AddBtn_clicked()
{

    AddWidget = new QWidget;
    QLabel *label1 = new QLabel(tr("姓名："));
    QLabel *label2 = new QLabel(tr("性别："));
    QLabel *label3 = new QLabel(tr("年龄"));
    QLabel *label4 = new QLabel(tr("编号："));
    QLabel *label5 = new QLabel(tr("地址："));

    NameEdit = new QLineEdit;
    SexEdit = new QLineEdit;
    AgeEdit = new QLineEdit;
    IdEdit = new QLineEdit;
    AddrEdit = new QLineEdit;

    OkBtn = new QPushButton(tr("确定"));
    CancelBtn = new QPushButton(tr("取消"));

    QGridLayout *mainLayout =new QGridLayout;
    mainLayout->addWidget(label1,0,0,1,1);
    mainLayout->addWidget(NameEdit,0,1,1,1);

    mainLayout->addWidget(label2,1,0,1,1);
    mainLayout->addWidget(SexEdit,1,1,1,1);

    mainLayout->addWidget(label3,2,0,1,1);
    mainLayout->addWidget(AgeEdit,2,1,1,1);

    mainLayout->addWidget(label4,3,0,1,1);
    mainLayout->addWidget(IdEdit,3,1,1,1);

    mainLayout->addWidget(label5,4,0,1,1);
    mainLayout->addWidget(AddrEdit,4,1,1,1);

    mainLayout->addWidget(OkBtn,5,0,1,1);
    connect(OkBtn,SIGNAL(clicked()),this,SLOT(slotOk()));
    mainLayout->addWidget(CancelBtn,5,1,1,1);
    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(slotCancel()));


    AddWidget->setLayout(mainLayout);
    AddWidget->show();

}

QVariant MISDemo::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)//如果是水平方向
        {
            switch(section)
            {
            case 0:
                return QString(tr("姓名"));
            case 1:
                return QString(tr("性别"));
            case 2:
                return QString(tr("年龄"));
            case 3:
                return QString(tr("编号"));
            case 4:
                return QString(tr("地址"));
            }
        }
        if(orientation == Qt::Vertical)//如果是垂直方向
        {
            switch(section)
            {
            case 0:
                return QString(tr("1.0"));
            case 1:
                return QString(tr("2.0"));
            case 2:
                return QString(tr("3.0"));
            case 3:
                return QString(tr("4.0"));
            case 4:
                return QString(tr("5.0"));
            }
        }
    }
    return QVariant();
}

QVariant MISDemo::data(const QModelIndex &index ,int role) const
{
    int row = index.row();
    int column = index.column();

   // QString str = "LSY";

    switch(role)
    {
    case Qt::DisplayRole://设置文本
        qDebug()<<tr("设置文本");
        break;
    case Qt::BackgroundColorRole://设置被景色
        if(row == 0 && column == 0)
        {
            QBrush brush(Qt::yellow);
            return brush;
        }
    case Qt::FontRole://设置字体
        if(row == 0 && column == 0)
        {
            QFont font;
            //font.setBold(true);
            font.setStyle(QFont::StyleOblique);//倾斜字体StyleOblique
            font.setPointSize(15);
            return font;
        }
    case Qt::TextAlignmentRole://设置文本对齐方式
        if(row == 0 && column == 0)
        {
            return Qt::AlignHCenter + Qt::AlignVCenter;
        }
    }


    return QVariant();
}

//单击弹出界面的确定
void MISDemo::slotOk()
{
    QString newName(NameEdit->text());
    QString newSex(SexEdit->text());
    QString newAge(AgeEdit->text());
    QString newId(IdEdit->text());
    QString newAddr(AddrEdit->text());


    if(newId == "")
    {
        QMessageBox::warning(this,tr("提示"),tr("请输入您的编号！"),QMessageBox::Yes);
        return;
    }

    QSqlRecord newRecord;
    newRecord.append(SqlModel->headerData(0,Qt::Horizontal).toString());
    newRecord.append(SqlModel->headerData(1,Qt::Horizontal).toString());
    newRecord.append(SqlModel->headerData(2,Qt::Horizontal).toString());
    newRecord.append(SqlModel->headerData(3,Qt::Horizontal).toString());
    newRecord.append(SqlModel->headerData(4,Qt::Horizontal).toString());


    newRecord.setValue(0,newName);
    newRecord.setValue(1,newSex);
    newRecord.setValue(2,newAge);
    newRecord.setValue(3,newId);
    newRecord.setValue(4,newAddr);
    //newRecord.setValue(1,newId.size());


      //  以上为创建新的记录，这个记录首先得有表头，这个表头和原来表的表头
       // 一致，才可以将新的记录插入进去。


    SqlModel->insertRecord(SqlModel->rowCount(),newRecord);//在最后一行插入数据
    SqlModel->select();
    AddWidget->close();
}
//单击弹出界面的取消
void MISDemo::slotCancel()
{
    AddWidget->close();
}

void MISDemo::on_FindStd_activated(const QString &arg1)
{
    //qDebug()<<tr("改变下表")<<FindStr;

  /*  QByteArray ba = FindStr.toLatin1();
    char * c_Str = ba.data();*/

    if(arg1 == tr("姓名") )
    {
        FindStr = "Name= ";
        qDebug()<<"NAME";
        return ;

    }

    if(arg1 == tr("性别"))
    {
        FindStr = "Sex=";
        qDebug()<<"SEX";
        return ;

    }

    if(arg1 == tr("年龄"))
    {
        FindStr = "Age=";
        qDebug()<<"AGE";
        return ;

    }

    if(arg1 == tr("编号"))
    {
        FindStr = "id=";
        qDebug()<<"ID";
        return ;

    }

    if(arg1 == tr("地址"))
    {
        FindStr = "addr=";
        qDebug()<<"ADDR";
        return ;

    }
}
