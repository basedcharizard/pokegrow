#include <iostream>
#include <ncurses.h>
#include "display.h"
#include "pokemon.h"

int main() 
{
	Nature *adamant = new Nature("Adamant", ATT, SPA);
	Nature *serious = new Nature("Serious");
	
	initscr();
	cbreak(); curs_set(0);
	Display *display = new Display;
	
	Pokemon garchomp(adamant);

	display->edit(&garchomp);

	delete display;
	delete adamant;
	delete serious;
	endwin();
	return 0;
}

