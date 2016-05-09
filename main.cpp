#include <iostream>
#include <iomanip>

using namespace std;

class Player {
private:
    string name;
    int score = 0;

public:

    Player(const string &name) : name(name) { }

    const string &getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }
};

class Engine {
private:
    Player *player;
public:
    Engine(Player *player) {
        this->player = player;
    }


    Player *getPlayer() const {
        return player;
    }
};

class Gui {
private:
    Engine *engine;
public:

    Gui() {
        int size;
        cout << u8"Velikost hraci plochy: ";
        cin >> size;
        cout << endl;


        string playerName;
        cout << u8"Jmeno hrace: ";
        cin >> playerName;
        cout << endl;

        Player *player = new Player(playerName);

        engine = new Engine(player);
    }

    void run() {

       cout << "Hrac :" << engine->getPlayer()->getName();
    }

};

int main() {
    Gui gui;
    gui.run();
}