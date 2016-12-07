#ifndef _display_h
#define _display_h
#include <ncurses.h>
#include <string>
#include "pokemon.h"
using namespace std;

WINDOW *new_window(int h, int w, int starty, int startx, bool border);
void destroy_window(WINDOW *w);


enum stat_t {
	BASE, IV, EV, FINAL
};


class Display {
	int height;
	int width;
	
	WINDOW *title_win;
	WINDOW *header_win;
	WINDOW *slot[7];
	WINDOW *msg_win;

	void setTitle(string title);
	void writeToSlot(int index,string text);
	string formatStats(enum stat_t f, int hp, int att, int def, int spa, int spd, int spe);
	string formatStats(enum stat_t f, int* stats);

	void paint(Pokemon p);

	public:
	Display();
	~Display();
	void edit(Pokemon p);
	void sendMsg(string msg);
	void wait();
};

class Command {
	public:
	char key;
	void run();
}

Command commands[3];

#endif
