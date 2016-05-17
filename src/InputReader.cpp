//
// Created by Pavel on 9.5.2016.
//

#include "InputReader.h"
#include <string>

using namespace std;


string InputReader::readString() {
    try {
        string txt;
        getline(cin, txt);
        return txt;
    } catch (...) {
        return readString();
    }
}

unsigned int InputReader::readUnsignedInteger() {
    try {
        string txt;
        getline(cin, txt);
        int number = (int) std::stoi(txt);
        if (number < 0) {
            cout << "Cislo musi byt klande, zkuste znovu:";
            return readUnsignedInteger();
        }
        return number;
    } catch (...) {
        cout << "Neplatne cislo, zkuste znovu:";
        return readUnsignedInteger();
    }
}

Coordinates *InputReader::readCoordinates(int size) {
    try {
        string txt;
        getline(cin, txt);

        int xInt = (int) txt[0];
        int yInt = stoi(txt.substr(1, 2));

        if (xInt < 65 || (xInt >= 65 + size && xInt < 97) || xInt >= 97 + size || txt.length() < 2 ||
            yInt >= size || yInt < 0) {
            cout << "Nesprvavne souradnice, zkuste znovu:";
            return readCoordinates(size);
        }

        int x = xInt >= 97 ? xInt - 97 : xInt - 65;
        int y = yInt;
        //cout << "souradnice: " << x << ":" << y << endl;
        return new Coordinates(x, y);
    } catch (...) {
        cout << "Nesprvavne souradnice, zkuste znovu:";
        return readCoordinates(size);
    }
}
