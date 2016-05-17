//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_ENGINE_H
#define PISKVORKY_ENGINE_H

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

    bool gameOver = false;

    void switchPlayers();

    void makeMoveAsBotPlayer();

public:
    Engine(string humanPlayerName, int size, int winningSize);

    ~Engine();

    void restart();

    void testBot2Move();

    /* return true on valid move */
    bool makeMove(int x, int y);

    int getStorageSize() const;

    Player *getStatus(int x, int y);

    bool isGameOver() const {
        return gameOver;
    }

    Player *getWinner() const {
        return isOnMove;
    }


    Player *getBotPlayer() const {
        return botPlayer;
    }

    Player *getHumanPlayer() const {
        return humanPlayer;
    }
};


#endif //PISKVORKY_ENGINE_H
