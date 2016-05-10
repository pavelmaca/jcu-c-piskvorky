//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_STORAGE_H
#define PISKVORKY_STORAGE_H

#include <iostream>

using namespace std;

class Storage {
private:
    int size;
    Player ***fields;

    bool checkDiagonals(int x, int y, int winningSize) {
        int inRow1 = 0;
        int inRow2 = 0;

        Player *currentPlayer = fields[x][y];

        int xBegin = x - winningSize > 0 ? x - winningSize : 0;
        int xEnd = x + winningSize < size ? x + winningSize : size - 1;

        int yBegin = y - winningSize > 0 ? y - winningSize : 0;
        int yEnd = y + winningSize < size ? y + winningSize : size - 1;

        // check newt winningSize -1 fields, end on right side of fields
        int yCurrent1 = yBegin;
        int yCurrent2 = yEnd;
        for (int xCurrent = xBegin; xCurrent <= xEnd; ++xCurrent) {
            if (fields[xCurrent][yCurrent1] != currentPlayer) {
                inRow1 = 0;
            } else if(yCurrent1 <= yEnd){
                if (++inRow1 == winningSize) return true;
            }

            if (fields[xCurrent][yCurrent2] != currentPlayer) {
                inRow2 = 0;
            } else if(yCurrent2 >= yBegin){
                if (++inRow2 == winningSize) return true;
            }

            yCurrent1++;
            yCurrent2--;
        }
        return false;
    }

    bool checkVertical(int x, int y, int winningSize) {
        int inRow = 0;

        Player *currentPlayer = fields[x][y];

        int yBegin = y - winningSize > 0 ? y - winningSize : 0;
        int yEnd = y + winningSize < size ? y + winningSize : size - 1;

        // check newt winningSize -1 fields, end on right side of fields
        for (int yCurrent = yBegin; yCurrent <= yEnd; ++yCurrent) {
            if (fields[x][yCurrent] != currentPlayer) {
                inRow = 0;
            } else {
                if (++inRow == winningSize) return true;
            }
        }
        return false;
    }

    bool checkHorizontal(int x, int y, int winningSize) {
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
    Storage(int size) {
        this->size = size;

        fields = new Player **[size];

        for (int x = 0; x < size; ++x) {
            fields[x] = new Player *[size];

            for (int y = 0; y < size; ++y) {
                fields[x][y] = NULL;
            }
        }
    }

    bool isEmpty(int x, int y) {
        return fields[x][y] == NULL;
    }

    void put(int x, int y, Player *player) {
        fields[x][y] = player;
    }

    bool checVictory(int x, int y, int winningSize) {
        if (isFull()) return false;

        return checkHorizontal(x, y, winningSize)
               || checkVertical(x, y, winningSize)
               || checkDiagonals(x, y, winningSize);
    }


    int getSize() const {
        return size;
    }

    Player *get(int x, int y) const {
        return fields[x][y];
    }

    bool isFull() {
        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {
                if (fields[x][y] == NULL) return false;
            }
        }
        return true;
    }
};

#endif //PISKVORKY_STORAGE_H
