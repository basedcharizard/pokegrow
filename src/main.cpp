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
	garchomp.setLevel(100);
	garchomp.setIV(ATT,31);
	garchomp.setEV(ATT,252);

	display->edit(garchomp);
	display->wait();

	delete display;
	endwin();
	return 0;
}

