#include "ftpclient.h"

FTPClient::FTPClient(QWidget *parent)
    : QDialog(parent)
{
    CreateFtpUi();
}

FTPClient::~FTPClient()
{


}

void FTPClient::CreateFtpUi()
{
     QFont font("ZYSong18030",12);
     setFont(font);
     LabelServer = new QLabel(tr("��������ַ��"));
     LineEditServer = new QLineEdit;
     LineEditServer->setText("ftp://92.214.25.254");
     labelUser = new QLabel(tr("�û�����"));
     LineEditUser = new QLineEdit;
     LineEditUser->setText("st22");
     LabelPassword = new QLabel(tr("���룺"));
     LineEditPassword = new QLineEdit;
     LineEditPassword->setText("st22825");

     LoginBtn = new QPushButton(tr("��¼"));
     connect(LoginBtn,SIGNAL(clicked()),this,SLOT(slotLogin()));
     PutBtn = new QPushButton(tr("�ϴ�"));
     PutBtn->setEnabled(false);
     connect(PutBtn,SIGNAL(clicked()),this,SLOT(slotPut()));
     GetBtn = new QPushButton(tr("����"));
     connect(GetBtn,SIGNAL(clicked()),this,SLOT(slotGet()));
     GetBtn->setEnabled(false);

     QGridLayout *GlMain = new QGridLayout;
     GlMain->addWidget(LabelServer,0,0,1,1);
     GlMain->addWidget(LineEditServer,0,1,1,1);

     GlMain->addWidget(labelUser,1,0,1,1);
     GlMain->addWidget(LineEditUser,1,1,1,1);

     GlMain->addWidget(LabelPassword,2,0,1,1);
     GlMain->addWidget(LineEditPassword,2,1,1,1);

     GlMain->addWidget(LoginBtn,3,0,1,2);

     GlMain->addWidget(PutBtn,4,0,1,1);
     GlMain->addWidget(GetBtn,4,1,1,1);

     setLayout(GlMain);
}


void FTPClient::slotLogin()
{
     QString serverAddress = LineEditServer->text();
     qDebug()<<tr("������ַ��")<<serverAddress;
     if(serverAddress.isEmpty())
     {
         QMessageBox::warning(this,tr("����"),tr("�������������ַ��"));
         return ;
     }

     QString userName = LineEditUser->text();
     qDebug()<<tr("�û�����")<<userName;
     if(userName.isEmpty())
     {
         QMessageBox::warning(this,tr("����"),tr("�������û�����"));
         return ;
     }

     QString Password = LineEditPassword->text();
     qDebug()<<tr("���룺")<<Password;
     if(Password.isEmpty())
     {
         QMessageBox::warning(this, tr("����"),tr("���������룡"));
         return ;
     }

     ftpc = new QFtp;
     ftpc->connectToHost("92.214.25.254");
     ftpc->login("st22","st22825");
     //����FTP������
     ftpc->setTransferMode(QFtp::Passive);


     if(ftpc->state() == QFtp::Unconnected )
         qDebug()<<tr("���������ϣ�");

     connect(ftpc,SIGNAL(stateChanged(int)),this,SLOT(slotStateChanged(int)));
     connect(ftpc,SIGNAL(done(bool)),this ,SLOT(slotDone(bool)));


     curStatus = LOGIN;
     qDebug()<<tr("��¼");
}
void FTPClient::slotPut()
{
    qDebug()<<tr("�ϴ�");
    bool ok;
    QString FileName = QInputDialog::getText(this,tr("�ϴ��ļ�"),tr("�������ļ�����"),QLineEdit::Normal,QString(),&ok);
    if(ok && !FileName.isEmpty())
    {
       QFile *remoteFileName = new QFile(FileName);
       ftpc->put(remoteFileName,FileName);
    }
    curStatus = PUT;
}
void FTPClient::slotGet()
{
    qDebug()<<tr("����");
    bool ok;
    QString FileName = QInputDialog::getText(this,tr("�����ļ�"),tr("�������ļ�����"),QLineEdit::Normal,QString(),&ok);
    if(ok && !FileName.isEmpty())
    {
        LocalFile = new QFile(FileName);
        LocalFile->open(QIODevice::WriteOnly);
        ftpc->get(FileName,LocalFile);
    }
    curStatus = GET;
}
void FTPClient::slotStateChanged(int state)
{
    qDebug()<<tr("�ı䰴ť״̬");
    //�����¼�ɹ�����ʹ�ܡ��ϴ����͡����ذ�ť��
    if(state == QFtp::LoggedIn)
    {
        PutBtn->setEnabled(true);
        GetBtn->setEnabled(true);
    }
}
void FTPClient::slotDone(bool error)
{
    qDebug()<<tr("����")<<error;
    if(error)
    {
         QMessageBox::warning(this,tr("����"),ftpc->errorString());
         return ;
    }

    if(curStatus == LOGIN)
    {
        qDebug()<<tr("��¼״̬");
        LoginBtn->setEnabled(false);
        curStatus = None;
    }

    if(curStatus == PUT)
    {
        qDebug()<<tr("�����ϴ�");
        QMessageBox::information(this,tr("��ʾ"),tr("�ϴ��ļ��ɹ�!"));
        curStatus = None;
    }

    if(curStatus == GET)
    {
        qDebug()<<tr("��������");
        QMessageBox::information(this,tr("��ʾ"),tr("�����ļ��ɹ�!"));
        curStatus = None;
    }
    /*
       QFtp::Unconnected ����δ����
       QFtp::HostLookup ���ڲ�ѯ����
       QFtp::Connecting ���ڳ�����������
       QFtp::Connected �Ѿ��ɹ���������
       QFtp::LoggedIn �Ѿ���¼�ɹ�
       QFtp::Closing l�������ڶϿ������Ͽ�����Unconnected��
    */
}
