#ifndef LISTCOUNTERS_H
#define LISTCOUNTERS_H

#include <QVector>
#include <QAbstractTableModel>

#include "CounterEntity.h"

class ListCounters : public QAbstractTableModel
{
private:
    QVector<CounterEntity> counters;

public:
    ListCounters(QObject* parent = nullptr);
    void AddCounter(CounterEntity counter);
    void AddNewCounter();
    void DeleteCounterByEntity(CounterEntity counter);
    void DeleteCounterByIndex(int index);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    void increaseCounter(int index);
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVector<CounterEntity> getCounters() const;
};

#endif // LISTCOUNTERS_H
