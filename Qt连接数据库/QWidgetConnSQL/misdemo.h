#ifndef MISDEMO_H
#define MISDEMO_H

#include <QtGui>
#include <QtSql>
#include <QSqlTableModel>

#include <QSqlDatabase>

namespace Ui {
    class MISDemo;
}

class MISDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit MISDemo(QWidget *parent = 0);
    ~MISDemo();
protected:

    //�������ݿ�
    bool ConnectDB();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index ,int role = Qt::DisplayRole) const;
    //��д�رպ���
    void closeEvent(QCloseEvent *);

    //������أ�����λ����Ϣ
    void ReadSetting();
    //�����˳���д��λ����Ϣ
    void WriteSetting();
    //�ж��Ƿ�ر�
    bool maybeSave();



private slots:
    void on_FindBtn_clicked();

    void on_DeleteBtn_clicked();

    void on_AddBtn_clicked();
    void slotOk();
    void slotCancel();

    void on_FindStd_currentIndexChanged(const QString &arg1);

private:
    Ui::MISDemo *ui;
    QSqlTableModel *SqlModel;
    //���ݿ��ļ�
     QSqlDatabase db;
    //�����ַ���
    QString FindStr;

    //����Ƿ������´����ݿ�ȡ����������
    bool m_flag ;

    //��ӶԻ���
    QWidget *AddWidget;

    QLineEdit *NameEdit;
    QLineEdit *SexEdit ;
    QLineEdit *AgeEdit ;
    QLineEdit *IdEdit ;
    QLineEdit *AddrEdit;

    QPushButton *OkBtn;
    QPushButton *CancelBtn;
};


#endif // MISDEMO_H
