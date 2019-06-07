#ifndef MISDEMO_H
#define MISDEMO_H

#include <QtGui>
#include <QtSql>
#include <QSqlTableModel>

namespace Ui {
    class MISDemo;
}

class MISDemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit MISDemo(QWidget *parent = 0);
    ~MISDemo();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index ,int role = Qt::DisplayRole) const;

private slots:
    void on_FindBtn_clicked();

    void on_DeleteBtn_clicked();

    void on_AddBtn_clicked();

    void on_FindStd_activated(const QString &arg1);

    void slotOk();
    void slotCancel();

private:
    Ui::MISDemo *ui;
    QSqlTableModel *SqlModel;
    QString FindStr;

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
