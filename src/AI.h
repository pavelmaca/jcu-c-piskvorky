//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_AI_H
#define PISKVORKY_AI_H


#include "Storage.h"
#include "CoordinatesBlock.h"

class AI {
    int winningSize;
    Storage *storage;

    int blocksNumber = 0;
    CoordinatesBlock **blocks;

    void generateBlocks();

    int getValueOnCoordinates(int x, int y);

    void countValueOfBlock(CoordinatesBlock *block);

    void updateBlockValues();


public:
    AI(int winningSize, Storage *storage);

    bool checkVictory();

    Coordinates *findBestCoordinates();

    ~AI();
};

#endif //PISKVORKY_AI_H
