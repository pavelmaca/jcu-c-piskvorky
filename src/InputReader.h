//
// Created by Pavel on 9.5.2016.
//

#ifndef PISKVORKY_INPUTREADER_H
#define PISKVORKY_INPUTREADER_H

#include <iostream>

using namespace std;

class InputReader {

public:
    static string readString() {
        try {
            string txt;
            cin >> txt;
            return txt;
        } catch (...) {
            return readString();
        }
    }

    static int readInteger() {
        // TODO nefunguje!!
        try {
            int number;
            cin >> number;
            return number;
        } catch (...) {
            return readInteger();
        }
    }

    static int *readCoorinates(int size) {
        int *coordinates = new int[2];
        string txt;
        cin >> txt;

        char x = txt[0];
        int xInt = (int) x;

        int yInt = std::stoi(txt.substr(1,1));;

        if (xInt < 65 || (xInt >= 65 + size && xInt < 97) || xInt >= 97 + size || txt.length() < 2 || yInt >= size || yInt < 0) {
            cout << "Nesprvavne souradnice";
            return readCoorinates(size);
        }

        coordinates[0] = xInt >= 97 ? xInt - 97 : xInt - 65;
        coordinates[1] = yInt;
        cout << "souradnice: " << coordinates[0] << ":" << coordinates[1] << endl;
/*
        cout << ((int) x) - 65 << endl;
        cout << ((int) 'A') - 65 << endl
        cout << ((int) 'a') - 97 << endl;
*/


        return coordinates;
    }
};

#endif //PISKVORKY_INPUTREADER_H
