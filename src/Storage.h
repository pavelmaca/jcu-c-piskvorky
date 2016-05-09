//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_STORAGE_H
#define PISKVORKY_STORAGE_H

#include <iostream>

using namespace std;

class Storage {
private:
    int size;
    Player ***fields;

public:
    Storage(int size) {
        this->size = size;

        fields = new Player**[size];

        for (int x = 0; x < size; ++x) {
            fields[x] = new Player*[size];

            for (int y = 0; y < size; ++y) {
                fields[x][y] = NULL;
            }
        }
    }

    bool isEmpty(int x, int y){
        return fields[x][y] == NULL;
    }

    void put(int x, int y, Player *player){
        fields[x][y] = player;
    }

    bool checVictory(int winningSize){
        return false;
    }


    int getSize() const {
        return size;
    }

    Player *get(int x, int y) const {
        return fields[x][y];
    }
};

#endif //PISKVORKY_STORAGE_H
