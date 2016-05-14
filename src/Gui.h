//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_GUI_H
#define PISKVORKY_GUI_H

#include "Engine.h"

class Gui {
private:
    Engine *engine;

    void printStatus();

    void printHeader(int size);

    void makePlayerMove();

    void printEndGame();

public:

    Gui();

    void runTest();

    void run();

    ~Gui();
};


#endif //PISKVORKY_GUI_H
