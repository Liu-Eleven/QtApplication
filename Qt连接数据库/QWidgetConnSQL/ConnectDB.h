#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <QSqlDatabase>

bool ConnectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");

    if( !db.open() )
    {
        return false;
    }else
    {
        return true;
    }

}

#endif // CONNECTDB_H
