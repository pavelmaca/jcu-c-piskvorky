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

    int arraySize = 0;

    /** našte např. všechny pětice (pokud hraji na 5) */
    Coordinates ***generateBlocks() {
        int leftOver = winningSize - 1;
        int numberOfBLockInLine = storage->getSize() - leftOver;
        arraySize = numberOfBLockInLine * 4 * storage->getSize();

        Coordinates ***blocks = new Coordinates **[arraySize];
        for (int i = 0; i < arraySize; ++i) {
            blocks[i] = new Coordinates *[winningSize];
            for (int j = 0; j < winningSize; ++j) {
                blocks[i][j] = NULL;
            }
        }

        int c = -3;

        for (int x = 0; x < storage->getSize(); ++x) {
            for (int y = 0; y < storage->getSize(); ++y) {
                c += 3;

                bool addHorizontal = (x < storage->getSize() - winningSize);
                bool addVertical = (y < storage->getSize() - winningSize);

                if (addHorizontal) c++;
                if (addVertical) c++;
                if (addHorizontal && addVertical) c++;

                for (int i = 0; i < winningSize; ++i) {
                    int g = c;
                    if (addHorizontal) {
                        // horizontal
                        blocks[g++][i] = new Coordinates(x + i, y);
                    }
                    if (addVertical) {
                        //vertical
                        blocks[g++][i] = new Coordinates(x, y + i);
                    }
                    if (addHorizontal && addVertical) {
                        //main diagonal
                        blocks[g++][i] = new Coordinates(x + i, y + i);
                    }
                }
            }
        }

        // slave diagonal only :(
        for (int x = storage->getSize() - 1; x >= leftOver; --x) {
            for (int y = storage->getSize() - 1; y >= leftOver; --y) {
                for (int i = 0; i < winningSize; ++i) {
                    blocks[c][i] = new Coordinates(x - i, y - i); // slave diagonal
                }
                c++;
            }
        }


        return blocks;

    }

    void getValueFromBLock(Coordinates ***blocks) {
        int attackPoints = 0;
        int defendPoints = 0;

        for (int i = 0; i < arraySize; ++i) {
            for (int j = 0; j < winningSize; ++j) {
                if (blocks[i][j] == NULL) continue;
                cout << blocks[i][j]->getX() << ":" << blocks[i][j]->getY() << endl;
            }
            cout << "----" << endl;
        }
    }


public:
    AI(int winningSize, Storage *storage) {
        this->winningSize = winningSize;
        this->storage = storage;
    }

    void test() {
        getValueFromBLock(generateBlocks());
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
