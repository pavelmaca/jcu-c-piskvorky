//
// Created by Pavel on 9.5.2016.
//

#include "Engine.h"
#include <string>
#include <iostream>

using namespace std;


void Engine::switchPlayers() {
    if (isOnMove == humanPlayer) {
        isOnMove = botPlayer;
        makeMoveAsBotPlayer();
    } else {
        isOnMove = humanPlayer;
    }
}

void Engine::makeMoveAsBotPlayer() {
    Coordinates *coordinates = ai->findBestCoordinates();

    cout << isOnMove->getName() << " tah: " << static_cast<char>('a' + coordinates->getX()) <<
    coordinates->getY() << endl;
    makeMove(coordinates->getX(), coordinates->getY());

    delete coordinates;
}

Engine::Engine(string humanPlayerName, int size, int winningSize) {
    this->botPlayer = new Player("PC", 'o');

    this->humanPlayer = new Player(humanPlayerName, 'x');
    this->isOnMove = this->humanPlayer;

    this->storage = new Storage(size);

    this->ai = new AI(winningSize, storage);
}

Engine::~Engine() {
    delete humanPlayer;
    delete botPlayer;
    delete ai;
    delete storage;
}

void Engine::restart() {
    this->isOnMove = this->humanPlayer;
    this->storage->clean();
    gameOver = false;
}

void Engine::testBot2Move() {
    ai->checkVictory();
    makeMoveAsBotPlayer();
}

/* return true on valid move */
bool Engine::makeMove(int x, int y) {
    if (!gameOver && storage->isEmpty(x, y)) {
        storage->put(x, y, isOnMove);
        gameOver = ai->checkVictory();

        if (storage->isFull()) {
            isOnMove = NULL;
            gameOver = true;
        }

        if (!gameOver) {
            switchPlayers();
        }

        if (gameOver && isOnMove != NULL) {
            isOnMove->addVictory();
        }

        return true;
    }
    return false;
}

int Engine::getStorageSize() const {
    return storage->getSize();
}

Player *Engine::getStatus(int x, int y) {
    return storage->get(x, y);
}

