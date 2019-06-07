#include "misdemo.h"
#include "ui_misdemo.h"

MISDemo::MISDemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MISDemo)
{
    ui->setupUi(this);

    ui->FindStd->addItem(tr("   "));
    ui->FindStd->addItem(tr("����"));
    ui->FindStd->addItem(tr("�Ա�"));
    ui->FindStd->addItem(tr("����"));
    ui->FindStd->addItem(tr("���"));
    ui->FindStd->addItem(tr("��ַ"));

    SqlModel = new QSqlTableModel(this);
    //��ȡ���ݿ��б�����ݣ�setTable(tablename)Ϊ����
    SqlModel->setTable("Student");
    //�ѱ��е����ݶ�ѡ�����
    SqlModel->select();

    SqlModel->setHeaderData(0,Qt::Horizontal,tr("����"));
    SqlModel->setHeaderData(1,Qt::Horizontal,tr("�Ա�"));
    SqlModel->setHeaderData(2,Qt::Horizontal,tr("����"));
    SqlModel->setHeaderData(3,Qt::Horizontal,tr("���"));
    SqlModel->setHeaderData(4,Qt::Horizontal,tr("��ַ"));
    //��SqlModel�е����ݷŵ�tableview��
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

   // QString str = "LSY";

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


    if(newId == "")
    {
        QMessageBox::warning(this,tr("��ʾ"),tr("���������ı�ţ�"),QMessageBox::Yes);
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


      //  ����Ϊ�����µļ�¼�������¼���ȵ��б�ͷ�������ͷ��ԭ����ı�ͷ
       // һ�£��ſ��Խ��µļ�¼�����ȥ��


    SqlModel->insertRecord(SqlModel->rowCount(),newRecord);//�����һ�в�������
    SqlModel->select();
    AddWidget->close();
}
//�������������ȡ��
void MISDemo::slotCancel()
{
    AddWidget->close();
}

void MISDemo::on_FindStd_activated(const QString &arg1)
{
    //qDebug()<<tr("�ı��±�")<<FindStr;

  /*  QByteArray ba = FindStr.toLatin1();
    char * c_Str = ba.data();*/

    if(arg1 == tr("����") )
    {
        FindStr = "Name= ";
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
}
