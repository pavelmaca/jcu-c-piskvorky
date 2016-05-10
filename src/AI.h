//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_AI_H
#define PISKVORKY_AI_H


#include <iostream>
#include "Storage.h"


class AI{

    int countHorizontalWeight(int x, int y){
        int inRow = 0;

        Player *currentPlayer = fields[x][y];

        int xBegin = x - winningSize > 0 ? x - winningSize : 0;
        int xEnd = x + winningSize < size ? x + winningSize : size - 1;

        // check newt winningSize -1 fields, end on right side of fields
        for (int xCurrent = xBegin; xCurrent <= xEnd; ++xCurrent) {
            if (fields[xCurrent][y] != currentPlayer) {
                inRow = 0;
            } else {
                if (++inRow == winningSize) return true;
            }
        }
        return false;
    }

public:
    int* getNextMove(Storage *storage){
        for (int x = 0; x < storage->getSize(); ++x) {
            for (int y = 0; y < storage->getSize(); ++y) {
                if(storage->isEmpty(x, y)){
                    return new int[2]{x, y};
                }
            }
        }
        //return new int[2]{0,0};
    }
};
#endif //PISKVORKY_AI_H
