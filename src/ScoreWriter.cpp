//
// Created by Pavel on 15.5.2016.
//

#include "ScoreWriter.h"
#include <fstream>
#include <string>

void ScoreWriter::saveScore(Player *player1, Player *player2) {
    fstream f(outputFile, fstream::out | fstream::app);

    if (f.is_open()) {
        f << player1->getName() << " " << player1->getScore() << ":"
        << player2->getScore() << " " << player2->getName() << endl;
        cout << "Data byla ulozena" << endl;
        f.close();
    }
    else
        cout << "Soubor '" << outputFile << "'se nepodarilo otevrit." << endl;
}

ScoreWriter::ScoreWriter(string outputFile) {
    this->outputFile = outputFile;
}



