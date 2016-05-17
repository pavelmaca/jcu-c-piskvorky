//
// Created by Pavel on 13.5.2016.
//

#include "CoordinatesBlock.h"
#include "Tools.h"

CoordinatesBlock::CoordinatesBlock(int size) {
    pCoordinates = new Coordinates *[size];
    this->size = size;
	this->i = 0;
	this->value = 0;
}

CoordinatesBlock::~CoordinatesBlock() {
	Tools::delete2DArray((Object***)&pCoordinates, i);
}

void CoordinatesBlock::add(int x, int y) {
    if (i < size) {
        pCoordinates[i++] = new Coordinates(x, y);
    } else throw exception();
}

void CoordinatesBlock::print() {
    for (int j = 0; j < i; ++j) {
        cout << pCoordinates[j]->getX() << ":" << pCoordinates[j]->getY() << endl;
    }
    cout << "---" << endl;
}

bool CoordinatesBlock::contains(int x, int y) {
    for (int j = 0; j < i; ++j) {
        if (pCoordinates[j]->getX() == x && pCoordinates[j]->getY() == y) {
            return true;
        }
    }
    return false;
}

Coordinates **CoordinatesBlock::getCoordinates() {
    return pCoordinates;
}
