#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "src/Gui.h"

int main() {
	system("PAUSE");
	Gui *gui = new Gui();
	
    //gui->runTest();
    gui->run();

	delete gui;

	_CrtDumpMemoryLeaks();
	system("PAUSE");
}