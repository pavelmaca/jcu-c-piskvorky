#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>


#include "src/Gui.h"
int main(int argc, char **argv) {
	//system("PAUSE");
    Gui *gui = new Gui();
	
    //gui->runTest();
    gui->run();
	gui->saveScore("history.txt");

	delete gui;

	//_CrtDumpMemoryLeaks();
	system("PAUSE");
}