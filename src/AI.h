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

    int blocksNumber = 0;
    CoordinatesBlock **blocks;

    Player *aiPlayer;

    /** našte např. všechny pětice (pokud hraji na 5) */
    void generateBlocks() {
        int leftOver = winningSize - 1;
        int numberOfBLockInLine = storage->getSize() - leftOver;
        // počet n-tic pro horizontální, nebo vertikální: (k-(n-1))*5
        blocksNumber = numberOfBLockInLine * storage->getSize() * 2;

        // počet ntic pro diagonály: k - (n-1) ^ 2
        blocksNumber += numberOfBLockInLine * numberOfBLockInLine * 2;

        blocks = new CoordinatesBlock *[blocksNumber];
        for (int i = 0; i < blocksNumber; ++i) {
            blocks[i] = NULL;
        }

        int c = 0;

        for (int x = 0; x < storage->getSize(); ++x) {
            for (int y = 0; y < storage->getSize(); ++y) {
                bool addHorizontal = (x <= storage->getSize() - winningSize);
                bool addVertical = (y <= storage->getSize() - winningSize);

                CoordinatesBlock *hBlock = NULL;
                CoordinatesBlock *vBlock = NULL;
                CoordinatesBlock *dBlock = NULL;

                if (addHorizontal) {
                    hBlock = new CoordinatesBlock(winningSize);
                    blocks[c++] = hBlock;
                }
                if (addVertical) {
                    vBlock = new CoordinatesBlock(winningSize);
                    blocks[c++] = vBlock;
                }
                if (addHorizontal && addVertical) {
                    dBlock = new CoordinatesBlock(winningSize);
                    blocks[c++] = dBlock;
                }

                for (int i = 0; i < winningSize; ++i) {
                    //int g = c;
                    if (hBlock != NULL) {
                        // horizontal
                        hBlock->add(x + i, y);
                        // blocks[g++][i] = new Coordinates(x + i, y);
                    }
                    if (vBlock != NULL) {
                        //vertical
                        vBlock->add(x, y + i);
                        // blocks[g++][i] = new Coordinates(x, y + i);
                    }
                    if (dBlock != NULL) {
                        //main diagonal
                        dBlock->add(x + i, y + i);
                        // blocks[g][i] = new Coordinates(x + i, y + i);
                    }
                }

            }
        }

        // slave diagonal only :(
        for (int x = 0; x < storage->getSize() - leftOver; ++x) {
            for (int y = storage->getSize() - 1; y >= leftOver; --y) {
                CoordinatesBlock *d2Block = new CoordinatesBlock(winningSize);
                blocks[c++] = d2Block;

                for (int i = 0; i < winningSize; ++i) {
                    d2Block->add(x + i, y - i);
                    // blocks[c][i] = new Coordinates(x - i, y - i); // slave diagonal
                }
            }
        }

    }

    int getValueOnCoordinates(int x, int y) {
        int pointsTotal = 0;

        for (int i = 0; i < blocksNumber; ++i) {
            if (blocks[i]->contains(x, y)) {
                pointsTotal += blocks[i]->value;
            }
        }

        return pointsTotal;
    }

    void updateBlockValues() {
        for (int i = 0; i < blocksNumber; ++i) {
            countValueOfBlock(blocks[i]);
        }
    }

    void countValueOfBlock(CoordinatesBlock *block) {
        int points = 0;
        Coordinates **coordinates = block->getCoordinates();

        bool layout[winningSize];

        Player *ownerOfBlock = NULL;
        for (int i = 0; i < winningSize; ++i) {
            Player *actualOwner = storage->get(coordinates[i]->getX(), coordinates[i]->getY());
            if (actualOwner != NULL) {
                if (ownerOfBlock == NULL)
                    ownerOfBlock = actualOwner;
                else if (ownerOfBlock != actualOwner) {
                    block->value = 0;
                    return;
                    //   return 0;
                }

                layout[i] = true;

                points++;
            } else {
                layout[i] = false;
            }
        }

        if (points == winningSize - 2 /*&& ownerOfBlock == aiPlayer*/) {
            if (!layout[0] && !layout[winningSize - 1]) {
                points += 100;
            }
        } else if (points == winningSize - 1) {
            points += 1000;
        }

        block->value = points + 1;
        //return points + 1;
    }

    void printBlocks() {
        for (int i = 0; i < blocksNumber; ++i) {
            blocks[i]->print();
        }
    }


public:
    AI(int winningSize, Storage *storage, Player *player) {
        this->winningSize = winningSize;
        this->storage = storage;
        this->aiPlayer = player;
        generateBlocks();
        /* printBlocks();
         string a;
         cin >> a;*/
    }

    Coordinates *findDumCoordinates() {
        for (int x = 0; x < storage->getSize(); ++x) {
            for (int y = 0; y < storage->getSize(); ++y) {
                if (storage->isEmpty(x, y)) {
                    return new Coordinates(x,y);
                }
            }
        }

        return NULL;
    }

    Coordinates *findBestCoordinates() {
        updateBlockValues();

        bool debug = true;

        int max = 0;
        Coordinates *maxCoordinates = NULL;
        if (debug) cout << "hodnoty:" << endl;
        for (int y = 0; y < storage->getSize(); ++y) {
            for (int x = 0; x < storage->getSize(); ++x) {
                if (!storage->isEmpty(x, y)) {
                    if (debug) cout << " |";
                    continue;
                }

                int val = getValueOnCoordinates(x, y);
                if (debug) cout << val << "|";
                if (val > max) {
                    max = val;
                    delete maxCoordinates;
                    maxCoordinates = new Coordinates(x, y);
                }
            }
            if (debug) cout << endl;
        }
        if (debug) cout << endl;

        return maxCoordinates;
    }
};

#endif //PISKVORKY_AI_H
