#ifndef COUNTERENTITY_H
#define COUNTERENTITY_H

class CounterEntity {
public:
    int id;
    int count;

    CounterEntity(int id, int count) : id(id), count(count) {}

    bool operator==(const CounterEntity &other) const{
        return id == other.id;
    }
};

#endif // COUNTERENTITY_H
