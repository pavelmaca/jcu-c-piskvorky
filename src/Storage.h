//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_STORAGE_H
#define PISKVORKY_STORAGE_H


#include "Player.h"

class Storage {
private:
    int size;
    Player ***fields;

public:
    Storage(int size);

    ~Storage();

    bool isEmpty(int x, int y);

    void put(int x, int y, Player *player);

    Player *get(int x, int y) const;

    bool isFull();

    void clean();

    int getSize() const {
        return size;
    }
};

#endif //PISKVORKY_STORAGE_H
