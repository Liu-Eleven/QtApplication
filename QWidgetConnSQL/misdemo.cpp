#include "misdemo.h"
#include "ui_misdemo.h"

MISDemo::MISDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MISDemo)
{
    ui->setupUi(this);
    setWindowTitle(tr("���ݿ�����"));
    //���ý������С�ı���ı�
    //this->setLayout(ui->centralWidget);
    //��ȡλ�ü�¼
    ReadSetting();


    ui->FindStd->addItem(tr("����"));
    ui->FindStd->addItem(tr("�Ա�"));
    ui->FindStd->addItem(tr("����"));
    ui->FindStd->addItem(tr("���"));
    ui->FindStd->addItem(tr("��ַ"));
    ui->FindStd->addItem(tr("��ʾȫ��"));
    //�±����Ǵ�0��ʼ
    ui->FindStd->setCurrentIndex(5);

  //  qDebug()<<"Current Index = "<<ui->FindStd->currentIndex();

    SqlModel = new QSqlTableModel(this);
    //��ȡ���ݿ��б�����ݣ�setTable(tablename)Ϊ����
    SqlModel->setTable("Student");
    qDebug()<<tr("m_flag��һ�θ�ֵ��")<<m_flag;
    //�ѱ��е����ݶ�ѡ�����
    SqlModel->select();

    SqlModel->setHeaderData(0,Qt::Horizontal,tr("����"));
    SqlModel->setHeaderData(1,Qt::Horizontal,tr("�Ա�"));
    SqlModel->setHeaderData(2,Qt::Horizontal,tr("����"));
    SqlModel->setHeaderData(3,Qt::Horizontal,tr("���"));
    SqlModel->setHeaderData(4,Qt::Horizontal,tr("��ַ"));
    //��SqlModel�е����ݷŵ�tableview��
    ui->tableView->setModel(SqlModel);
    //���ò��ñ༭���
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
            QMessageBox::about(this,tr("����"),tr("���ݿ��ѯʧ�ܣ�"));
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
    int state = QMessageBox::warning(this,tr("ɾ��"),tr("��ȷ��Ҫɾ��������"),
                                     QMessageBox::Yes | QMessageBox::No);
    if(state == QMessageBox::No)
    {
        return ;
    }else
    {
        //��ȡѡ����
        int curRow = ui->tableView->currentIndex().row();
        SqlModel->removeRow(curRow);
    }
}

void MISDemo::on_AddBtn_clicked()
{

    AddWidget = new QWidget;
    QLabel *label1 = new QLabel(tr("������"));
    QLabel *label2 = new QLabel(tr("�Ա�"));
    QLabel *label3 = new QLabel(tr("����"));
    QLabel *label4 = new QLabel(tr("��ţ�"));
    QLabel *label5 = new QLabel(tr("��ַ��"));

    NameEdit = new QLineEdit;
    SexEdit = new QLineEdit;
    AgeEdit = new QLineEdit;
    IdEdit = new QLineEdit;
    AddrEdit = new QLineEdit;

    OkBtn = new QPushButton(tr("ȷ��"));
    CancelBtn = new QPushButton(tr("ȡ��"));

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
        if(orientation == Qt::Horizontal)//�����ˮƽ����
        {
            switch(section)
            {
            case 0:
                return QString(tr("����"));
            case 1:
                return QString(tr("�Ա�"));
            case 2:
                return QString(tr("����"));
            case 3:
                return QString(tr("���"));
            case 4:
                return QString(tr("��ַ"));
            }
        }
        if(orientation == Qt::Vertical)//����Ǵ�ֱ����
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
    case Qt::DisplayRole://�����ı�
        qDebug()<<tr("�����ı�");
        break;
    case Qt::BackgroundColorRole://���ñ���ɫ
        if(row == 0 && column == 0)
        {
            QBrush brush(Qt::yellow);
            return brush;
        }
    case Qt::FontRole://��������
        if(row == 0 && column == 0)
        {
            QFont font;
            //font.setBold(true);
            font.setStyle(QFont::StyleOblique);//��б����StyleOblique
            font.setPointSize(15);
            return font;
        }
    case Qt::TextAlignmentRole://�����ı����뷽ʽ
        if(row == 0 && column == 0)
        {
            return Qt::AlignHCenter + Qt::AlignVCenter;
        }
    }


    return QVariant();
}

//�������������ȷ��
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
        QMessageBox::warning(this,tr("��ʾ"),tr("���������ı�ţ�"),QMessageBox::Yes);
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


      //  ����Ϊ�����µļ�¼�������¼���ȵ��б�ͷ�������ͷ��ԭ����ı�ͷ
       // һ�£��ſ��Խ��µļ�¼�����ȥ��

    QSqlQuery query;//����ִ�����SQL���
    query.prepare("insert into student values(?,?,?,?,?)");
    query.addBindValue(newName);
    query.addBindValue(newSex);
    query.addBindValue(newAge);
    query.addBindValue(newId);
    query.addBindValue(newAddr);
    bool flag;
    flag = query.exec();

   // flag = SqlModel->insertRecord(SqlModel->rowCount(),newRecord);//�����һ�в�������
    qDebug()<<flag;
    SqlModel->select();
    AddWidget->close();
}
//�������������ȡ��
void MISDemo::slotCancel()
{
    AddWidget->close();
}

/*
  �������������ַ�ʽ��һ������ÿ�ֲ���ѡ���£�Ĭ�ϰ����ݿ������ѡ���ã����ǲ������б�
  Ҳ���ǰ����ݱ����ں�̨����������ɽ��У�����ע�⣺����������������ַ�ʽ������ͬ��ʾ����
  һ������Ϊִ�е�ʱ���Ƚ��뱾����ִ��currentindex=0��Ҳ������ִ������Ȼ���ٻص����캯��
  ȥִ�������ġ�
  ��һ���Ǵ����ݿ��в��ң�����Ҫ�õ����ݿ���������ʵ�����ַ�ʽ��Ϊ�õĲ��ҷ�ʽ��
*/
void MISDemo::on_FindStd_currentIndexChanged(const QString &)
{
    int i_find = ui->FindStd->currentIndex();
    qDebug()<<"Current Index = "<<i_find;
    //���û�ѡ����ʾȫ��ʱ���༭���ܽ��б༭
    //���û�ѡ��0~4ѡ��ʱ�����Խ��б༭
    switch(i_find)
    {
    case 0:
        if(!m_flag)
        {
            qDebug()<<tr("�����ˣ�");
            SqlModel->setTable("Student");
            SqlModel->select();
        }

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "Name=";
        break;
    case 1:
        //�����½��棬ָ�ں�̨��ȡ��������.���������ʱ����ɽ�����ҡ�
        SqlModel->select();

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "Sex=";
        qDebug()<<"SEX";
        break;
    case 2:
        //�����½��棬ָ�ں�̨��ȡ��������.���������ʱ����ɽ�����ҡ�
        SqlModel->select();

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "Age=";
        qDebug()<<"AGE";
        break;
    case 3:
        //�����½��棬ָ�ں�̨��ȡ��������.���������ʱ����ɽ�����ҡ�
        SqlModel->select();

        ui->FindEdit->setReadOnly(false);
        ui->FindEdit->setText("");
        FindStr = "id=";
        qDebug()<<"ID";
        break;
    case 4:
        //�����½��棬ָ�ں�̨��ȡ��������.���������ʱ����ɽ�����ҡ�
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
        /*�������m_flag����ʶ����ôĬ��ѡ��Ϊ����ʾȫ��������ʼ����ʱ���Ѿ���ʾȫ��һ�Σ�����������ʾһ��
            ϵͳ�������*/
        if(!m_flag)
        {
            qDebug()<<tr("�����ˣ�");
            SqlModel->setTable("Student");
            SqlModel->select();
        }
        m_flag = false;
        break;
    default:
        qDebug()<<tr("�����ˣ�");
    }

   /* if(arg1 == tr("����") )
    {
        //��ֵ���������ַ���
        FindStr = "Name=";
        qDebug()<<"NAME";
        return ;

    }

    if(arg1 == tr("�Ա�"))
    {
        FindStr = "Sex=";
        qDebug()<<"SEX";
        return ;

    }

    if(arg1 == tr("����"))
    {
        FindStr = "Age=";
        qDebug()<<"AGE";
        return ;

    }

    if(arg1 == tr("���"))
    {
        FindStr = "id=";
        qDebug()<<"ID";
        return ;

    }

    if(arg1 == tr("��ַ"))
    {
        FindStr = "addr=";
        qDebug()<<"ADDR";
        return ;

    }
    if(arg1 == tr("��ʾȫ��"))
    {
        ui->FindEdit->setText("");
        SqlModel->setTable("Student");
        SqlModel->select();
        ui->tableView->setModel(SqlModel);
    }*/
}

void MISDemo::closeEvent(QCloseEvent *event)
{
    qDebug()<<tr("�رմ��ڣ�");
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
    int state = QMessageBox::warning(this,tr("�ر�"),tr("��ȷ��Ҫ�˳�������"),
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

//������أ�����λ����Ϣ
void MISDemo::ReadSetting()
{
    //�������ݿ�
    if( !ConnectDB() )
    {
        QMessageBox::about(this,tr("��ʾ"),tr("���ݿ��ʧ�ܣ�\n"));
        exit(-1);
    }
    QSettings Settings("LSY","Qt Connect SQL");
    QPoint pos=Settings.value("pos",QPoint(330,310)).toPoint();
    QSize size = Settings.value("size",QSize(400,400)).toSize();

    //���������С
    resize(size);
    //�Ѵ����ƶ���posλ��
    move(pos);
}
//�����˳���д��λ����Ϣ
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

