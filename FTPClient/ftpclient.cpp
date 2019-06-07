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
     LabelServer = new QLabel(tr("服务器地址："));
     LineEditServer = new QLineEdit;
     LineEditServer->setText("ftp://92.214.25.254");
     labelUser = new QLabel(tr("用户名："));
     LineEditUser = new QLineEdit;
     LineEditUser->setText("st22");
     LabelPassword = new QLabel(tr("密码："));
     LineEditPassword = new QLineEdit;
     LineEditPassword->setText("st22825");

     LoginBtn = new QPushButton(tr("登录"));
     connect(LoginBtn,SIGNAL(clicked()),this,SLOT(slotLogin()));
     PutBtn = new QPushButton(tr("上传"));
     PutBtn->setEnabled(false);
     connect(PutBtn,SIGNAL(clicked()),this,SLOT(slotPut()));
     GetBtn = new QPushButton(tr("下载"));
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
     qDebug()<<tr("主机地址：")<<serverAddress;
     if(serverAddress.isEmpty())
     {
         QMessageBox::warning(this,tr("错误"),tr("请输入服务器地址！"));
         return ;
     }

     QString userName = LineEditUser->text();
     qDebug()<<tr("用户名：")<<userName;
     if(userName.isEmpty())
     {
         QMessageBox::warning(this,tr("错误"),tr("请输入用户名！"));
         return ;
     }

     QString Password = LineEditPassword->text();
     qDebug()<<tr("密码：")<<Password;
     if(Password.isEmpty())
     {
         QMessageBox::warning(this, tr("错误"),tr("请输入密码！"));
         return ;
     }

     ftpc = new QFtp;
     ftpc->connectToHost("92.214.25.254");
     ftpc->login("st22","st22825");
     //连接FTP服务器
     ftpc->setTransferMode(QFtp::Passive);


     if(ftpc->state() == QFtp::Unconnected )
         qDebug()<<tr("就是连不上！");

     connect(ftpc,SIGNAL(stateChanged(int)),this,SLOT(slotStateChanged(int)));
     connect(ftpc,SIGNAL(done(bool)),this ,SLOT(slotDone(bool)));


     curStatus = LOGIN;
     qDebug()<<tr("登录");
}
void FTPClient::slotPut()
{
    qDebug()<<tr("上传");
    bool ok;
    QString FileName = QInputDialog::getText(this,tr("上传文件"),tr("请输入文件名："),QLineEdit::Normal,QString(),&ok);
    if(ok && !FileName.isEmpty())
    {
       QFile *remoteFileName = new QFile(FileName);
       ftpc->put(remoteFileName,FileName);
    }
    curStatus = PUT;
}
void FTPClient::slotGet()
{
    qDebug()<<tr("下载");
    bool ok;
    QString FileName = QInputDialog::getText(this,tr("下载文件"),tr("请输入文件名："),QLineEdit::Normal,QString(),&ok);
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
    qDebug()<<tr("改变按钮状态");
    //如果登录成功，则使能“上传”和“下载按钮”
    if(state == QFtp::LoggedIn)
    {
        PutBtn->setEnabled(true);
        GetBtn->setEnabled(true);
    }
}
void FTPClient::slotDone(bool error)
{
    qDebug()<<tr("错误")<<error;
    if(error)
    {
         QMessageBox::warning(this,tr("错误"),ftpc->errorString());
         return ;
    }

    if(curStatus == LOGIN)
    {
        qDebug()<<tr("登录状态");
        LoginBtn->setEnabled(false);
        curStatus = None;
    }

    if(curStatus == PUT)
    {
        qDebug()<<tr("单击上传");
        QMessageBox::information(this,tr("提示"),tr("上传文件成功!"));
        curStatus = None;
    }

    if(curStatus == GET)
    {
        qDebug()<<tr("单击下载");
        QMessageBox::information(this,tr("提示"),tr("下载文件成功!"));
        curStatus = None;
    }
    /*
       QFtp::Unconnected 主机未连接
       QFtp::HostLookup 正在查询主机
       QFtp::Connecting 正在尝试连接主机
       QFtp::Connected 已经成功连接主机
       QFtp::LoggedIn 已经登录成功
       QFtp::Closing l连接正在断开，（断开后是Unconnected）
    */
}
