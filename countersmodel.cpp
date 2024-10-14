#include "countersmodel.h"


CountersModel::CountersModel(ListCounters* list, QObject* parent)
    : QAbstractTableModel(parent), listCounters(list) {}

int CountersModel::rowCount(const QModelIndex& parent) const {
    return listCounters->GetCounters().size();
}

int CountersModel::columnCount(const QModelIndex& parent) const {
    return 2;
}

QVariant CountersModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    const auto counters = listCounters->GetCounters();
    const CounterEntity& counter = counters[index.row()];

    if (index.column() == 0) {
        return counter.id;
    } else if (index.column() == 1) {
        return counter.count;
    }

    return QVariant();
}

QVariant CountersModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section == 0)
            return QString("ID");
        else if (section == 1)
            return QString("Count");
    }

    return QVariant();
}
