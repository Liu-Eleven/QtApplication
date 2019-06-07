#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include <QtSql>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());


    //添加数据库驱动
    QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
    //加载数据库
    dbconn.setDatabaseName("mytest.db");

    if( !dbconn.open()  )
    {
        qDebug()<<"Open my database failure!";
    }

    QSqlQuery query;//以下执行相关SQL语句
    query.exec("create table student(id varchar,name text)");

    query.exec(QObject::tr("insert into student values(1,'刘世一')"));
    query.exec(QObject::tr("insert into student values(2,'任海征')"));
    query.exec(QObject::tr("insert into student values(3,'张  雅')"));
    query.exec(QObject::tr("insert into student values(4,'牛心愿')"));

    query.exec(QObject::tr("select * from student"));

    while(query.next())//query.next()指向查找到的第一条记录然后每次后移一条记录
    {
        int ele0 = query.value(0).toInt();
        QString ele1 = query.value(1).toString();
        qDebug()<<ele0<<ele1;
    }


    return a.exec();
}
