//
// Created by Assassik on 11. 5. 2016.
//

#ifndef PISKVORKY_COORDINATES_H
#define PISKVORKY_COORDINATES_H

#include <iostream>
#include "Object.h"

using namespace std;

class Coordinates : public Object{
private:
    int x;
    int y;
public:
    Coordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};

#endif //PISKVORKY_COORDINATES_H
