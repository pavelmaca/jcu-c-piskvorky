//
// Created by Pavel on 9.5.2016.
//

#include "Gui.h"
#include "InputReader.h"
#include "ScoreWriter.h"

using namespace std;


void Gui::printStatus() {
    // clean console output
    // source: http://stackoverflow.com/a/6487534
    //cout << "\x1B[2J\x1B[H";
    //system("clr");

    int size = engine->getStorageSize();
    printHeader(size);

    for (int y = 0; y < size; ++y) {
        cout << " " << (y <= 9 ? " " : "") << y;
        for (int x = 0; x < size; ++x) {
            Player *field = engine->getStatus(x, y);
            char symbol = (field == NULL ? ' ' : field->getSymbol());
            cout << '|' << symbol;
        }
        cout << '|' << endl;
    }

}

void Gui::printHeader(int size) {
    int x = 0;
    cout << "   ";
    for (; x < size; x++) {
        cout << '|' << static_cast<char>('a' + x);
    }
    cout << '|' << endl;
}

void Gui::makePlayerMove() {
    cout << "Vas tah:";
    Coordinates *coordinates = InputReader::readCoordinates(engine->getStorageSize());

    bool result = engine->makeMove(coordinates->getX(), coordinates->getY());
    delete coordinates;
    if (!result) {
        cout << "Neplatný tah, zkuste znovu." << endl;
        return makePlayerMove();
    }
}

void Gui::printEndGame() {
    cout << "==========" << endl;
    Player *winner = engine->getWinner();
    if (winner == NULL) {
        cout << "Remíza" << endl;
    } else {
        cout << winner->getName() << " zvitezil." << endl;
    }


    cout << "Chcete hrat znovu? (A/n)" << endl;
    string restart;
    getline(cin, restart);

    if (restart == "A" || restart == "a") {
        engine->restart();
        this->run();
    } else {
        cout << "KONEC HRY" << endl;
    }
}


Gui::Gui() {

    int maxSize = 26;

    cout << "Vitej ve hry piskvorky," << endl
    << "Prvni vyberte nastaveni hry." << endl << endl;

    int winningSize;
    bool validWinningSize = false;
    while (!validWinningSize) {
        cout << "Vyherni pocet: ";
        winningSize = InputReader::readUnsignedInteger();
        cout << endl;

        if (winningSize > 0 && winningSize <= maxSize - 2) {
            validWinningSize = true;
        } else {
            cout << "Vyherni pocet musi byt v rozmezi 1-" << (maxSize - 2) << endl
            << "Zkuste to znovu." << endl;
        }
    }


    int size = 0;
    bool validSize = false;
    int minimumSize = winningSize + 2;
    while (!validSize) {
        cout << "Velikost hraci plochy: ";
        size = InputReader::readUnsignedInteger();
        cout << endl;

        if (size >= minimumSize && maxSize >= size) {
            validSize = true;
        } else {
            cout << "Velikost hraci plochy musi byt " << minimumSize << "-" << maxSize << endl
            << "Zkuste to znovu." << endl;
        }
    }


    string playerName;
    cout << "Jmeno hrace: ";
    playerName = InputReader::readString();
    cout << endl;

    cout << "Vas znak je: x" << endl
    << "Souradnice zadavejte ve tvaru: a5" << endl << endl;

    engine = new Engine(playerName, size, winningSize);
}

void Gui::runTest() {
    while (!engine->isGameOver()) {
        engine->testBot2Move();
    }

    printStatus();
    printEndGame();
}

void Gui::run() {
    printStatus();

    while (!engine->isGameOver()) {
        makePlayerMove();
        printStatus();
    }

    printEndGame();
}

Gui::~Gui() {
    delete engine;
}

void Gui::saveScore(string file) {
    ScoreWriter scoreWriter(file);
    scoreWriter.saveScore(engine->getHumanPlayer(), engine->getBotPlayer());
}



