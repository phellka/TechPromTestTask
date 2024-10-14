#include "listcounters.h"

ListCounters::ListCounters(QObject* parent) : QAbstractTableModel(parent){
    counters = QVector<CounterEntity>();
}

void ListCounters::AddCounter(CounterEntity counter){
    if (counters.contains(counter)){
        return;
    }
    int row = counters.size();
    beginInsertRows(QModelIndex(), row, row);
    counters.append(counter);
    endInsertRows();
}

void ListCounters::AddNewCounter(){
    int newId = 0;
    for (int i = 0; i < counters.size(); ++i){
        if (counters[i].id >= newId){
            newId = counters[i].id + 1;
        }
    }
    CounterEntity newEntity(newId, 0);
    int row = counters.size();
    beginInsertRows(QModelIndex(), row, row);
    counters.append(newEntity);
    endInsertRows();
}

void ListCounters::DeleteCounterByEntity(CounterEntity counter){
    int row = counters.indexOf(counter);
    if (row >= 0) {
        beginRemoveRows(QModelIndex(), row, row);
        counters.removeOne(counter);
        endRemoveRows();
    }
}

void ListCounters::DeleteCounterByIndex(int index){
    if (index < 0 || index >= counters.size()){
        return;
    }
    beginRemoveRows(QModelIndex(), index, index);
    counters.removeAt(index);
    endRemoveRows();
}

int ListCounters::rowCount(const QModelIndex& parent) const {
    return counters.size();
}

int ListCounters::columnCount(const QModelIndex& parent) const {
    return 2;
}

void ListCounters::increaseCounter(int index){
    if (index < 0 || index >= counters.size()){
        return;
    }
    counters[index].count++;
    QModelIndex modelIndex = createIndex(index, 1);
    emit dataChanged(modelIndex, modelIndex, {Qt::DisplayRole});
}

QVariant ListCounters::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    const CounterEntity& counter = counters[index.row()];

    if (index.column() == 0) {
        return counter.id;
    } else if (index.column() == 1) {
        return counter.count;
    }

    return QVariant();
}

QVariant ListCounters::headerData(int section, Qt::Orientation orientation, int role) const {
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

QVector<CounterEntity> ListCounters::getCounters() const {
    return counters;
}
