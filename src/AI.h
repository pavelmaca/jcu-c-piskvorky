//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_AI_H
#define PISKVORKY_AI_H


#include <iostream>
#include "Storage.h"
#include "Coordinates.h"

class AI {
    int winningSize;
    Storage *storage;

    /** našte např. všechny pětice (pokud hraji na 5) */
    Coordinates ***getBlocks(int x, int y) {
        Coordinates ***blocks = new Coordinates **[winningSize * 4]; // 4 = počet směrů
        for (int i = 0; i < winningSize * 4; ++i) {
            blocks[i] = new Coordinates *[winningSize]; //
            for (int j = 0; j < winningSize; ++j) { //init elements in array
                blocks[i][j] = NULL;
            }
        }

        int currentGroup = 0;

        int xBegin = x - winningSize >= 0 ? x - winningSize + 1 : 0;
        int xEnd = x + winningSize < storage->getSize() ? x + winningSize - 1 : storage->getSize() - 1;

        int yBegin = y - winningSize >= 0 ? y - winningSize + 1 : 0;
        int yEnd = y + winningSize < storage->getSize() ? y + winningSize - 1 : storage->getSize() - 1;


        // HORIZONTAL
        // z řádku udělá n-tice, kde n = výherní počet
        /*
         for (int xOffset = 0; xOffset <= xEnd - xBegin - winningSize + 1; ++xOffset) {
               // všechny n-tice uloží do pole
               for (int i = 0; i < winningSize; ++i) {
                   blocks[currentGroup][i] = new Coordinates(xOffset + xBegin + i, y);
               }
               currentGroup++;
           }*/

        // VERTICAL
        // z řádku udělá n-tice, kde n = výherní počet
        /* for (int yOffset = 0; yOffset <= yEnd - yBegin - winningSize + 1; ++yOffset) {
             // všechny n-tice uloží do pole
             for (int i = 0; i < winningSize; ++i) {
                 blocks[currentGroup][i] = new Coordinates(x, yOffset + yBegin + i);
             }
             currentGroup++;
         }*/

        // diagonal from left top to right down


        return getMainDiagonalBlocks(x, y);
    }

    Coordinates ***createEmptyBlocks(){
        Coordinates ***blocks = new Coordinates **[winningSize];
        for (int i = 0; i < winningSize; ++i) {
            blocks[i] = new Coordinates *[winningSize]; //
            for (int j = 0; j < winningSize; ++j) { //init elements in array
                blocks[i][j] = NULL;
            }
        }

        return blocks;
    }

    /** našte např. všechny pětice (pokud hraji na 5) */
    Coordinates ***getMainDiagonalBlocks(int x, int y) {
        Coordinates ***blocks = createEmptyBlocks();

        int currentGroup = 0;

        int dXBegin = 0;
        int dYEnd = 0;
        for (int xyOffset = 0; xyOffset <= xEnd - xBegin - winningSize + 1 && xyOffset <= yEnd - yBegin - winningSize + 1; ++xyOffset) {
            // všechny n-tice uloží do pole
            for (int i = 0; i < winningSize; ++i) {
                blocks[currentGroup][i] = new Coordinates(xyOffset + xBegin + i, xyOffset + yBegin + i);
            }
            currentGroup++;
        }

    }

        void getValueFromBLock(Coordinates ***blocks) {
        int attackPoints = 0;
        int defendPoints = 0;

        for (int i = 0; i < winningSize * 4; ++i) {
            for (int j = 0; j < winningSize; ++j) {
                if (blocks[i][j] == NULL) continue;
                cout << blocks[i][j]->getX() << ":" << blocks[i][j]->getY() << endl;
            }
        }
    }


public:
    AI(int winningSize, Storage *storage) {
        this->winningSize = winningSize;
        this->storage = storage;
    }

    void test() {
        getValueFromBLock(getBlocks(2, 3));
    }

    int *getNextMove(Storage *storage) {
        for (int x = 0; x < storage->getSize(); ++x) {
            for (int y = 0; y < storage->getSize(); ++y) {
                if (storage->isEmpty(x, y)) {
                    return new int[2]{x, y};
                }
            }
        }
        //return new int[2]{0,0};
    }
};

#endif //PISKVORKY_AI_H
