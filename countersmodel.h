#ifndef COUNTERSMODEL_H
#define COUNTERSMODEL_H

    #include <QAbstractTableModel>
#include "CounterEntity.h"
#include "ListCounters.h"

class CountersModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    ListCounters* listCounters;
public:
    CountersModel(ListCounters* list, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // COUNTERSMODEL_H
