//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_ENGINE_H
#define PISKVORKY_ENGINE_H

#include <string>
#include <iostream>
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
    int winningSize;

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
        Coordinates *coordinates = ai->findBestCoordinates();

		cout << isOnMove->getName() << " tah: " << static_cast<char>('a' + coordinates->getX()) << coordinates->getY() << endl;
        makeMove(coordinates->getX(), coordinates->getY());

        delete[] coordinates;
    }

public:
    Engine(string humanPlayerName, int size, int winningSize) {
        this->winningSize = winningSize;
        this->botPlayer = new Player("PC", 'o');

        this->humanPlayer = new Player(humanPlayerName, 'x');
        this->isOnMove = this->humanPlayer;

        this->storage = new Storage(size);

        this->ai = new AI(winningSize, storage);
    }

    void testBot2Move(){
        ai->checkVictory();
        makeMoveAsBotPlayer();
    }
    bool makeMove(int x, int y) {
        if (!gameOver && storage->isEmpty(x, y)) {
            storage->put(x, y, isOnMove);
            gameOver = ai->checkVictory();

            if( storage->isFull()){
                isOnMove = NULL;
                gameOver = true;
            }

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

    Player* getWinner() const {
        return isOnMove;
    }
};


#endif //PISKVORKY_ENGINE_H
