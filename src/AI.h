//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_AI_H
#define PISKVORKY_AI_H


#include <iostream>
#include "Storage.h"
#include "Coordinates.h"
#include <random>


class WinException : public exception {

};


class AI {
    int winningSize;
    Storage *storage;

    int blocksNumber = 0;
    CoordinatesBlock **blocks;

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
                    if (hBlock != NULL) {
                        hBlock->add(x + i, y); // horizontal
                    }
                    if (vBlock != NULL) {
                        vBlock->add(x, y + i);  //vertical
                    }
                    if (dBlock != NULL) {
                        dBlock->add(x + i, y + i); //main diagonal
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
                }

                layout[i] = true;

                points++;
            } else {
                layout[i] = false;
            }
        }

        if (points == winningSize - 2) {
            if (!layout[0] && !layout[winningSize - 1]) {
                points += 100;
            }
        } else if (points == winningSize - 1) {
            points += 1000;
        } else if(points == winningSize){
            throw WinException();
        }

        block->value = points + 1;
    }

    void updateBlockValues() {
        for (int i = 0; i < blocksNumber; ++i) {
            countValueOfBlock(blocks[i]);
        }
    }


public:
    AI(int winningSize, Storage *storage) {
        this->winningSize = winningSize;
        this->storage = storage;
        generateBlocks();
    }

    Coordinates *findDumCoordinates() {
        for (int x = 0; x < storage->getSize(); ++x) {
            for (int y = 0; y < storage->getSize(); ++y) {
                if (storage->isEmpty(x, y)) {
                    return new Coordinates(x, y);
                }
            }
        }

        return NULL;
    }

    bool checkVictory() {
        try {
            updateBlockValues();
        } catch (WinException &e) {
            return true;
        }
        return false;
    }

    Coordinates *findBestCoordinates() {
        bool debug = false;

        int max = -1;
        int maxCount = 0;
        int maxCountLimit = 100;
        Coordinates **maxCoordinates = new Coordinates*[maxCountLimit];
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
                    //delete maxCoordinates;
                    maxCount = 0;
                    maxCoordinates[maxCount++] = new Coordinates(x, y);
                }else if(val == max && maxCount < maxCountLimit){
                    maxCoordinates[maxCount++] = new Coordinates(x, y);
                }
            }
            if (debug) cout << endl;
        }
        if (debug) cout << endl;

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 eng(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, maxCount - 1); // define the range

        int random = distr(eng);

        Coordinates *result = new Coordinates(maxCoordinates[random]->getX(), maxCoordinates[random]->getY());
        delete[] maxCoordinates;
        return result;
    }

    ~AI(){
        cout << "Call AI destructor" << endl;

       /* for (int i = 0; i < blocksNumber; ++i) {
            delete[] blocks;
        }***/
    }
};

#endif //PISKVORKY_AI_H
