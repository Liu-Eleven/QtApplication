#include "misdemo.h"
#include "ui_misdemo.h"

MISDemo::MISDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MISDemo)
{
    ui->setupUi(this);
    setWindowTitle(tr("数据库连接"));
    //设置界面随大小改变而改变
    //this->setLayout(ui->centralWidget);
    //读取位置记录
    ReadSetting();


    ui->FindStd->addItem(tr("姓名"));
    ui->FindStd->addItem(tr("性别"));
    ui->FindStd->addItem(tr("年龄"));
    ui->FindStd->addItem(tr("编号"));
    ui->FindStd->addItem(tr("地址"));
    ui->FindStd->addItem(tr("显示全部"));
    //下标仍是从0开始
    ui->FindStd->setCurrentIndex(5);

  //  qDebug()<<"Current Index = "<<ui->FindStd->currentIndex();

    SqlModel = new QSqlTableModel(this);
    //读取数据库中表的内容，setTable(tablename)为表名
    SqlModel->setTable("Student");
    qDebug()<<tr("m_flag第一次赋值！")<<m_flag;
    //把表中的内容都选择出来
    SqlModel->select();

    SqlModel->setHeaderData(0,Qt::Horizontal,tr("姓名"));
    SqlModel->setHeaderData(1,Qt::Horizontal,tr("性别"));
    SqlModel->setHeaderData(2,Qt::Horizontal,tr("年龄"));
    SqlModel->setHeaderData(3,Qt::Horizontal,tr("编号"));
    SqlModel->setHeaderData(4,Qt::Horizontal,tr("地址"));
    //将SqlModel中的内容放到tableview中
    ui->tableView->setModel(SqlModel);
    //设置不让编辑表格
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    update();
}

MISDemo::~MISDemo()
{
    delete ui;
}

void MISDemo::on_FindBtn_clicked()
{
    int ResultCount;
    qDebug()<<"on_FindBtn_clicked--->"<<FindStr;

   /* if(FindStr == "Age=")
    {
        qDebug()<<"lsyrhz";
        QSqlQuery query;
       // int numRows;
        bool flag ;
        query.prepare("select * from Student where age=?");
        query.addBindValue(CtrStr);
        flag = query.exec();
        if(!flag)
        {
            QMessageBox::about(this,tr("警告"),tr("数据库查询失败！"));
            return ;
        }
        SqlModel->insertRowIntoTable(query.record());
        while(query.next())
        {
            QString name = query.value(0).toString();
            qDebug()<<name;
        }
        return;
    }*/

    QString itemFiter(FindStr);
    itemFiter += "\"" +  ui->FindEdit->text() + "\"";
    SqlModel->setFilter(itemFiter);
    ResultCount = SqlModel->rowCount();
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

    qDebug()<<NameEdit->text()<<SexEdit->text();


    if(newId == "")
    {
        QMessageBox::warning(this,tr("提示"),tr("请输入您的编号！"),QMessageBox::Yes);
        return;
    }

    /*QSqlRecord newRecord;
    newRecord.append(SqlModel->headerData(0,Qt::Horizontal).toString());
    qDebug()<<SqlModel->headerData(0,Qt::Horizontal).toString();
    newRecord.append(SqlModel->headerData(1,Qt::Horizontal).toString());
    newRecord.append(SqlModel->headerData(2,Qt::Horizontal).toString());
    newRecord.append(SqlModel->headerData(3,Qt::Horizontal).toString());
    newRecord.append(SqlModel->headerData(4,Qt::Horizontal).toString());

    qDebug()<<newName;
    newRecord.setValue(0,newName);
    newRecord.setValue(1,newSex);
    newRecord.setValue(2,newAge);
    newRecord.setValue(3,newId);
    newRecord.setValue(4,newAddr);
    //newRecord.setValue(1,newId.size());*/


      //  以上为创建新的记录，这个记录首先得有表头，这个表头和原来表的表头
       // 一致，才可以将新的记录插入进去。

    QSqlQuery query;//以下执行相关SQL语句
    query.prepare("insert into student values(?,?,?,?,?)");
    query.addBindValue(newName);
    query.addBindValue(newSex);
    query.addBindValue(newAge);
    query.addBindValue(newId);
    query.addBindValue(newAddr);
    bool flag;
    flag = query.exec();

   // flag = SqlModel->insertRecord(SqlModel->rowCount(),newRecord);//在最后一行插入数据
    qDebug()<<flag;
    SqlModel->select();
    AddWidget->close();
}
//单击弹出界面的取消
void MISDemo::slotCancel()
{
    AddWidget->close();
}

/*
  查找数据有两种方式，一种是在每种查找选项下，默认把数据库的所有选项获得，但是不更新列表，
  也就是把数据保存在后台，而查找则可进行，但是注意：姓名这项不可以用这种方式，道理同显示所有
  一样，因为执行的时候，先进入本函数执行currentindex=0，也就是先执行姓名然后再回到构造函数
  去执行其它的。
  另一种是从数据库中查找，这则要用到数据库查找命令。其实这两种方式都为好的查找方式。
*/
void MISDemo::on_FindStd_currentIndexChanged(const QString &)
{
    int i_find = ui->FindStd->currentIndex();
    qDebug()<<"Current Index = "<<i_find;
    //当用户选择：显示全部时，编辑框不能进行编辑
    //当用户选择0~4选项时，可以进行编辑
    switch(i_find)
    {
    case 0:
        if(!m_flag)
        {
            qDebug()<<tr("进来了！");
            SqlModel->setTable("Student");
            SqlModel->select();
        }

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "Name=";
        break;
    case 1:
        //不更新界面，指在后台获取所有数据.当点击查找时，亦可进入查找。
        SqlModel->select();

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "Sex=";
        qDebug()<<"SEX";
        break;
    case 2:
        //不更新界面，指在后台获取所有数据.当点击查找时，亦可进入查找。
        SqlModel->select();

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "Age=";
        qDebug()<<"AGE";
        break;
    case 3:
        //不更新界面，指在后台获取所有数据.当点击查找时，亦可进入查找。
        SqlModel->select();

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "id=";
        qDebug()<<"ID";
        break;
    case 4:
        //不更新界面，指在后台获取所有数据.当点击查找时，亦可进入查找。
        SqlModel->select();

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "addr=";
        qDebug()<<"ADDR";
        break;
    case 5:
        ui->FindEdit->setText("");
        ui->FindEdit->setReadOnly(true);
        qDebug()<<"lsyrhz--->"<<m_flag;
        /*如果不用m_flag来标识，那么默认选项为：显示全部，而初始化的时候已经显示全部一次，而这里又显示一次
            系统会崩溃！*/
        if(!m_flag)
        {
            qDebug()<<tr("进来了！");
            SqlModel->setTable("Student");
            SqlModel->select();
        }
        m_flag = false;
        break;
    default:
        qDebug()<<tr("出错了！");
    }

   /* if(arg1 == tr("姓名") )
    {
        //把值赋给查找字符串
        FindStr = "Name=";
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
    if(arg1 == tr("显示全部"))
    {
        ui->FindEdit->setText("");
        SqlModel->setTable("Student");
        SqlModel->select();
        ui->tableView->setModel(SqlModel);
    }*/
}

void MISDemo::closeEvent(QCloseEvent *event)
{
    qDebug()<<tr("关闭窗口！");
    if (maybeSave()) {
        WriteSetting();
        event->accept();
        db.close();

    } else {
        event->ignore();
    }

}

bool MISDemo::maybeSave()
{
    bool flag;
    int state = QMessageBox::warning(this,tr("关闭"),tr("您确定要退出程序吗？"),
                                     QMessageBox::Yes | QMessageBox::No);
    if(state == QMessageBox::No)
    {
        flag = false;
    }else
    {
        flag = true;
    }
    return flag;

}

//程序加载，读入位置信息
void MISDemo::ReadSetting()
{
    //连接数据库
    if( !ConnectDB() )
    {
        QMessageBox::about(this,tr("提示"),tr("数据库打开失败！\n"));
        exit(-1);
    }
    QSettings Settings("LSY","Qt Connect SQL");
    QPoint pos=Settings.value("pos",QPoint(330,310)).toPoint();
    QSize size = Settings.value("size",QSize(400,400)).toSize();

    //调整窗体大小
    resize(size);
    //把窗体移动到pos位置
    move(pos);
}
//程序退出，写入位置信息
void MISDemo::WriteSetting()
{
    QSettings settings("LSY","Qt Connect SQL");
    settings.setValue("pos",pos());
    settings.setValue("size",size());
}

bool MISDemo::ConnectDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");

    if( !db.open() )
    {
        return false;
    }else
    {
        return true;
    }

}

