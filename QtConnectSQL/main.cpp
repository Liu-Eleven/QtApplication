#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include <QtSql>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());


    //������ݿ�����
    QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
    //�������ݿ�
    dbconn.setDatabaseName("mytest.db");

    if( !dbconn.open()  )
    {
        qDebug()<<"Open my database failure!";
    }

    QSqlQuery query;//����ִ�����SQL���
    query.exec("create table student(id varchar,name text)");

    query.exec(QObject::tr("insert into student values(1,'����һ')"));
    query.exec(QObject::tr("insert into student values(2,'�κ���')"));
    query.exec(QObject::tr("insert into student values(3,'��  ��')"));
    query.exec(QObject::tr("insert into student values(4,'ţ��Ը')"));

    query.exec(QObject::tr("select * from student"));

    while(query.next())//query.next()ָ����ҵ��ĵ�һ����¼Ȼ��ÿ�κ���һ����¼
    {
        int ele0 = query.value(0).toInt();
        QString ele1 = query.value(1).toString();
        qDebug()<<ele0<<ele1;
    }


    return a.exec();
}
