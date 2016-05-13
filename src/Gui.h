//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_GUI_H
#define PISKVORKY_GUI_H

#include <iostream>
#include "Engine.h"
#include "InputReader.h"
#include <stdlib.h>
#include <random>

using namespace std;

class Gui {
private:
    Engine *engine;

    void printStatus() {
        // clean console output
        // source: http://stackoverflow.com/a/6487534
        //std::cout << "\x1B[2J\x1B[H";
        //system("clr");

        int size = engine->getStorageSize();
        printHeader(size);

        for (int y = 0; y < size; ++y) {
            int x = 0;
            cout << " " << (y <= 9 ? " " : "") << y;
            for (; x < size; x++) {
                Player *field = engine->getStatus(x, y);
                char symbol = field == NULL ? ' ' : field->getSymbol();
                cout << '|' << symbol;
            }
            cout << '|' << endl;
        }

    }

    void printHeader(int size) {
        int x = 0;
        cout << "   ";
        for (; x < size; x++) {
            cout << '|' << static_cast<char>('a' + x);
        }
        cout << '|' << endl;
    }

    void makePlayerMove() {
        cout << "Vas tah:";
        Coordinates *coordinates = InputReader::readCoorinates(engine->getStorageSize());

        bool result = engine->makeMove(coordinates->getX(), coordinates->getY());
        delete coordinates;
        if (!result) {
            cout << "Neplatný tah, zkuste znovu." << endl;
            makePlayerMove();
        }
    }

    void printEndGame() {
        cout << "==========" << endl;
        Player *winner = engine->getWinner();
        if (winner == NULL) {
            cout << "Remíza" << endl;
        } else {
            cout << winner->getName() << " zvítězil." << endl;
        }

        cout << "KONEC HRY" << endl;

        //engine restart
    }

public:

    Gui() {
        setlocale(LC_ALL, "cs_CZ.UTF-8");

        int winningSize;
        cout << "Výherní počet: ";
        winningSize = InputReader::readUnsignInteger();
        cout << endl;

        int size;
        cout << "Velikost hrací plochy: ";
        size = InputReader::readUnsignInteger();
        cout << endl;

        string playerName;
        cout << "Jméno hráče: ";
        playerName = InputReader::readString();
        cout << endl;

        engine = new Engine(playerName, size, winningSize);
    }

    void runTest() {
        // http://stackoverflow.com/a/7560564
      /*  std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, engine->getStorageSize() - 1); // define the range

        int x = distr(eng);
        int y = distr(eng);
        cout << "souradnice: " << x << ":" << y << endl;
      */

        while (!engine->isGameOver()) {
            engine->testBot2Move();
        }

        printStatus();
        printEndGame();
    }

    void run() {
        printStatus();


        while (!engine->isGameOver()) {
            system("clear");

            makePlayerMove();
            printStatus();
        }

        printEndGame();
    }
};


#endif //PISKVORKY_GUI_H
