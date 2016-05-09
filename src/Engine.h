//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_ENGINE_H
#define PISKVORKY_ENGINE_H

#include <iostream>
#include "Player.h"
#include "Storage.h"

using namespace std;

class Engine {
private:
    Player *humanPlayer;
    Player *botPlayer;

    Player *isOnMove;

    Storage *storage;
    int winningSize = 5;
public:
    Engine(string humanPlayerName, int size) {
        this->botPlayer = new Player("PC", 'o');

        this->humanPlayer = new Player(humanPlayerName, 'x');
        this->isOnMove = this->humanPlayer;

        this->storage = new Storage(size);
    }

    bool createMove(int x, int y) {
        if (storage->isEmpty(x, y)) {
            storage->put(x, y, isOnMove);
            storage->checVictory(winningSize);
            return true;
        }
        return false;
    }


    int getStorageSize() const {
        return storage->getSize();
    }

    Player *getStatus(int x, int y){
        return storage->get(x, y);
    }
};


#endif //PISKVORKY_ENGINE_H
