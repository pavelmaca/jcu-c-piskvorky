//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_GUI_H
#define PISKVORKY_GUI_H

#include <iostream>
#include "Engine.h";
#include "InputReader.h";
#include <stdlib.h>

using namespace std;

class Gui {
private:
    Engine *engine;

    void printStatus() {
        // clean console output
        // source: http://stackoverflow.com/a/6487534
        //TODO std::cout << "\x1B[2J\x1B[H";

        int size = engine->getStorageSize();
        printHeader(size);


        for (int y = 0; y < size; ++y) {
            int x = 0;
            cout << " " << y;
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
        cout << "  ";
        for (; x < size; x++) {
            cout << '|' << static_cast<char>('a' + x);
        }
        cout << '|' << endl;
    }

    void makePlayerMove(){
        cout << "Vas tah:";
        int *coordinates = InputReader::readCoorinates(engine->getStorageSize());

        engine->createMove(coordinates[0], coordinates[1]);
    }

public:

    Gui() {
        int size;
        size = 5; //InputReader::readInteger();
        cout << endl;


        string playerName;
        cout << u8"Jmeno hrace: ";
        playerName = "Pavel"; //InputReader::readString();
        cout << endl;

        engine = new Engine(playerName, size);
    }

    void run() {
        printStatus();

        //while(engine->isGameOver()){
            makePlayerMove();
            printStatus();
       // }

        cout << "GAME OVER" << endl;
        //engine restart

        pause();
    }

    void pause(){

        cin.get();
    }

};


#endif //PISKVORKY_GUI_H
