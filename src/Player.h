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
    int score = 0;
    char symbol;

public:

    Player(const string &name, char symbol) : name(name), symbol(symbol) { }

    virtual ~Player() {
        cout << "Player destructor called" << endl;
    }


    string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }


    char getSymbol() const {
        return symbol;
    }
};


#endif //PISKVORKY_PLAYER_H
