#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QtGui>
#include <QtNetwork>

class FTPClient : public QDialog
{
    Q_OBJECT

public:
    FTPClient(QWidget *parent = 0);
    ~FTPClient();

private slots:
    void slotLogin();
    void slotPut();
    void slotGet();
    void slotStateChanged(int state);
    void slotDone(bool error);

private:
    QLabel *LabelServer;
    QLineEdit *LineEditServer;
    QLabel *labelUser;
    QLineEdit *LineEditUser;
    QLabel *LabelPassword;
    QLineEdit *LineEditPassword;

    QPushButton *LoginBtn;
    QPushButton *PutBtn;
    QPushButton *GetBtn;

    enum STATUS{None , LOGIN, PUT,GET};
    STATUS curStatus;

    QFtp *ftpc;
    QFile *LocalFile;

   void CreateFtpUi();
};

#endif // FTPCLIENT_H
