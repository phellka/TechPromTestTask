#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QMessageBox>

#include "CounterEntity.h"

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect();
    bool createTable();
    bool saveCounters(const QVector<CounterEntity>& counters);
    QVector<CounterEntity> loadCounters();

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
