//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_ENGINE_H
#define PISKVORKY_ENGINE_H

#include <iostream>
#include "Player.h"
#include "Storage.h"
#include "AI.h"

using namespace std;

class Engine {
private:
    Player *humanPlayer;
    Player *botPlayer;
    Player *isOnMove;

    AI *ai;

    Storage *storage;
    int winningSize = 3;

    bool gameOver = false;

    void switchPlayers() {
        if (isOnMove == humanPlayer) {
            isOnMove = botPlayer;
            makeMoveAsBotPlayer();
        } else {
            isOnMove = humanPlayer;
        }
    }

    void makeMoveAsBotPlayer(){
        int *coordinates = ai->getNextMove(storage);
        makeMove(coordinates[0], coordinates[1]);

        delete[] coordinates;
    }

public:
    Engine(string humanPlayerName, int size) {
        this->botPlayer = new Player("PC", 'o');

        this->humanPlayer = new Player(humanPlayerName, 'x');
        this->isOnMove = this->humanPlayer;

        this->storage = new Storage(size);

        this->ai = new AI(winningSize, storage);
        this->ai->test();
    }

    bool makeMove(int x, int y) {
        if (!gameOver && storage->isEmpty(x, y)) {
            storage->put(x, y, isOnMove);
            gameOver = storage->checVictory(x, y, winningSize); // TODO

            if (!gameOver) {
                switchPlayers();
            }

            return true;
        }
        return false;
    }

    int getStorageSize() const {
        return storage->getSize();
    }

    Player *getStatus(int x, int y) {
        return storage->get(x, y);
    }


    bool isGameOver() const {
        return gameOver;
    }
};


#endif //PISKVORKY_ENGINE_H
