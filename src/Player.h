//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_PLAYER_H
#define PISKVORKY_PLAYER_H

#include <iostream>

using namespace std;

class Player {
private:
    string name;
    char symbol;
    unsigned int score = 0;

public:

    Player(const string &name, char symbol) : name(name), symbol(symbol) { }

    string getName() const {
        return name;
    }

    char getSymbol() const {
        return symbol;
    }

    void addVictory(){
        score++;
    }

    unsigned int getScore() const {
        return score;
    }
};


#endif //PISKVORKY_PLAYER_H
