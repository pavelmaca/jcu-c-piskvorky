#include "src/Gui.h"

int main(int argc, char **argv) {
    Gui gui;
    gui.run();
	gui.saveScore("history.txt");
}