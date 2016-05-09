//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_GUI_H
#define PISKVORKY_GUI_H

#include <iostream>
#include "Engine.h";

using namespace std;

class Gui {
private:
    Engine *engine;

    void printStatus(){
        int size = engine->getStorageSize();
        printHeader(size);


        for (int y = 0; y < size ; ++y) {
            int x = 0;
            cout << " " << y;
            for (; x < size; x++) {
                Player *field = engine->getStatus(x, y);
                char symbol = field == NULL ? ' ' : field->getSymbol();
                cout << '|' << symbol;
            }
            cout << endl;
        }

    }

    void printHeader(int size){

        int x = 0;
        cout << "  |";
        for (; x < size-1; x++) {
            cout << x << '|';
        }
        cout << x+1 << endl;
    }

public:

    Gui() {
        int size;
        cout << u8"Velikost hraci plochy: ";
        cin >> size;
        cout << endl;


        string playerName;
        cout << u8"Jmeno hrace: ";
        cin >> playerName;
        cout << endl;

        engine = new Engine(playerName, size);
    }

    void run() {
        printStatus();
        cout << engine->createMove(0,0) << endl;
        printStatus();
        cout << engine->createMove(0,1) << endl;
        printStatus();
        cout <<  engine->createMove(1,0) << endl;
        printStatus();
    }

};


#endif //PISKVORKY_GUI_H
