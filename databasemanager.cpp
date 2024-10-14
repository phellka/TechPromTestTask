#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("counters.db");
}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::connect() {
    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::createTable() {
    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS counters ("
                          "id INTEGER PRIMARY KEY, "
                          "count INTEGER)";
    if (!query.exec(createTable)) {
        qDebug() << "Create Table Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::saveCounters(const QVector<CounterEntity>& counters) {
    QSqlQuery query;
    if (!query.exec("DELETE FROM counters")) {
        qDebug() << "Delete Error: " << query.lastError().text();
        return false;
    }
    for (const CounterEntity& counter : counters) {
        query.prepare("INSERT INTO counters (id, count) VALUES (:id, :count)");
        query.bindValue(":id", counter.id);
        query.bindValue(":count", counter.count);
        if (!query.exec()) {
            qDebug() << "Insert Error: " << query.lastError().text();
            return false;
        }
    }
    return true;
}


QVector<CounterEntity> DatabaseManager::loadCounters() {
    QVector<CounterEntity> counters;
    QSqlQuery query("SELECT id, count FROM counters");
    while (query.next()) {
        int id = query.value(0).toInt();
        int count = query.value(1).toInt();
        counters.append(CounterEntity(id, count));
    }
    return counters;
}
