//
// Created by Pavel on 9.5.2016.
//

#include "Storage.h"

Storage::Storage(int size) {
    this->size = size;

    fields = new Player **[size];

    for (int x = 0; x < size; ++x) {
        fields[x] = new Player *[size];

        for (int y = 0; y < size; ++y) {
            fields[x][y] = NULL;
        }
    }
}

Storage::~Storage() {
    cout << "Storage destructor called" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            delete fields[i][j];
        }
        delete fields[i];
    }
    delete fields;
}

bool Storage::isEmpty(int x, int y) {
    return fields[x][y] == NULL;
}

void Storage::put(int x, int y, Player *player) {
    fields[x][y] = player;
}

Player *Storage::get(int x, int y) const {
    return fields[x][y];
}

bool Storage::isFull() {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            if (fields[x][y] == NULL) return false;
        }
    }
    return true;
}

void Storage::clean() {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            fields[x][y] = NULL;
        }
    }
}
