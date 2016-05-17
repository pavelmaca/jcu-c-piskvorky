//
// Created by Pavel on 15.5.2016.
//

#ifndef PISKVORKY_SCOREWRITER_H
#define PISKVORKY_SCOREWRITER_H


#include "Player.h"
class ScoreWriter {
private:
    string outputFile;
public:
    ScoreWriter(string outputFile);
    void saveScore(Player *player1, Player *player2);
};


#endif //PISKVORKY_SCOREWRITER_H
