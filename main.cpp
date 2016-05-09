#include <iostream>
#include <iomanip>

using namespace std;

class Player {
private:
    string name;
    string score = 0;
public:
    Player(string name) {
        this->name = name;
    }

    const string &getName() const {
        return name;
    }

    const string &getScore() const {
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

        Player player(playerName);

        engine = new Engine(&player);
    }

    void run() {

        cout << "Hrac :" << engine->getPlayer()->getName();
    }

};

int main() {
    Gui gui;
    gui.run();
}