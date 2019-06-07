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

    //连接数据库
    bool ConnectDB();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index ,int role = Qt::DisplayRole) const;
    //重写关闭函数
    void closeEvent(QCloseEvent *);

    //程序加载，读入位置信息
    void ReadSetting();
    //程序退出，写入位置信息
    void WriteSetting();
    //判断是否关闭
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
    //数据库文件
     QSqlDatabase db;
    //查找字符串
    QString FindStr;

    //标记是否再重新从数据库取出所有数据
    bool m_flag ;

    //添加对话框
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
