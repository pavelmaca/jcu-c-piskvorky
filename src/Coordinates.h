//
// Created by Assassik on 11. 5. 2016.
//

#ifndef PISKVORKY_COORDINATES_H
#define PISKVORKY_COORDINATES_H


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

class CoordinatesBlock {
private:
    Coordinates **pCoordinates;
    int i = 0;
    int size;
public:
    int value;

    CoordinatesBlock(int size) {
        pCoordinates = new Coordinates *[size];
        this->size = size;
    }

    ~CoordinatesBlock() {
        for (int j = 0; j < i; ++j) {
            delete pCoordinates[i];
        }

        delete pCoordinates;
    }

    void add(int x, int y) {
        if (i < size) {
            pCoordinates[i++] = new Coordinates(x, y);
        }else throw exception();
    }

    void print(){
        for (int j = 0; j < i; ++j) {
            cout << pCoordinates[j]->getX() << ":" << pCoordinates[j]->getY() << endl;
        }
        cout << "---" << endl;
    }

    bool contains(int x, int y){
        for (int j = 0; j < i; ++j) {
            if(pCoordinates[j]->getX() == x && pCoordinates[j]->getY() == y){
                return true;
            }
        }
        return false;
    }

    Coordinates** getCoordinates(){
        return pCoordinates;
    }

};

#endif //PISKVORKY_COORDINATES_H
