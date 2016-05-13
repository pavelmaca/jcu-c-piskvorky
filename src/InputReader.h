//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_INPUTREADER_H
#define PISKVORKY_INPUTREADER_H

#include <iostream>
#include <string>

using namespace std;

class InputReader {

public:
    static string readString() {
        try {
            string txt;
            getline(cin, txt);
            return txt;
        } catch (...) {
            return readString();
        }
    }

    static unsigned int readUnsignInteger() {
        try {
            string txt;
            getline(cin, txt);
            unsigned int number = std::stoi( txt);
            if(number < 0) {
                cout << "Cislo musi byt klande, zkuste znovu:";
                return readUnsignInteger();
            }
            return  number;
        } catch (...) {
            cout << "Neplatne cislo, zkuste znovu:";
            return readUnsignInteger();
        }
    }

    static Coordinates* readCoorinates(int size) {
        try {
            string txt;
            getline(cin, txt);

            int xInt = (int) txt[0];
            int yInt = stoi(txt.substr(1, 1));;

            if (xInt < 65 || (xInt >= 65 + size && xInt < 97) || xInt >= 97 + size || txt.length() < 2 ||
                yInt >= size || yInt < 0) {
                cout << "Nesprvavne souradnice, zkuste znovu:";
                return readCoorinates(size);
            }

            int x  = xInt >= 97 ? xInt - 97 : xInt - 65;
            int y = yInt;
            //cout << "souradnice: " << x << ":" << y << endl;
            return new Coordinates(x, y);
        }catch(...){
            cout << "Nesprvavne souradnice, zkuste znovu:";
            readCoorinates(size);
        }
    }
};

#endif //PISKVORKY_INPUTREADER_H
