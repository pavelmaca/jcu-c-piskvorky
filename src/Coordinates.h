//
// Created by Assassik on 11. 5. 2016.
//

#ifndef PISKVORKY_COORDINATES_H
#define PISKVORKY_COORDINATES_H

#include <iostream>

using namespace std;

class Coordinates {
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

    ~Coordinates() {
        cout << "deleting coordinates" << endl;
    }
};

#endif //PISKVORKY_COORDINATES_H
