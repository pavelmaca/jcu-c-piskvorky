//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_INPUTREADER_H
#define PISKVORKY_INPUTREADER_H

#include "Coordinates.h"

using namespace std;

class InputReader {

public:
    static string readString();

    static unsigned int readUnsignedInteger();

    static Coordinates *readCoordinates(int size);
};

#endif //PISKVORKY_INPUTREADER_H
