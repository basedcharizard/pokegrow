#include <iostream>
#include <ncurses.h>
#include "display.h"
#include "pokemon.h"

int main() 
{
	
	initscr();
	raw(); noecho(); curs_set(0);
	Display *display = new Display;
	
	Pokemon garchomp;
	garchomp.setEV(ATT,252);
	garchomp.setEV(DEF,4);
	garchomp.setEV(SPE,252);

	display->edit(garchomp);
	display->wait();

	delete display;
	endwin();
	return 0;
}

