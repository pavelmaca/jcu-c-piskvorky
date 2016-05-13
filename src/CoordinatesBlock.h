//
// Created by Pavel on 13.5.2016.
//

#ifndef PISKVORKY_COORDINATESBLOCK_H
#define PISKVORKY_COORDINATESBLOCK_H

#include "Coordinates.h"

class CoordinatesBlock {
private:
    Coordinates **pCoordinates;
    int i = 0;
    int size;
public:
    int value;

    CoordinatesBlock(int size);

    ~CoordinatesBlock();

    void add(int x, int y);

    void print();

    bool contains(int x, int y);

    Coordinates **getCoordinates();
};


#endif //PISKVORKY_COORDINATESBLOCK_H
