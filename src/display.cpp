#include <cstring>
#include "display.h"

Display::Display() 
{
	getmaxyx(stdscr,height,width);

	title_win = new_window(3, 14, 0, 0, true);
	header_win = new_window(3, width-15, 0, 15, true);
	for (int i=0;i<8;i++) {
		slot[i] = new_window(3, width, (i*3), 0, true);
	}
	msg_win = new_window(height, width, 0, 0, false);
	//////// commands
	// TODO: implement command system
	// 		 wgetch a command string, then parse
	// 		 m i 3 31 // modify IV for def to 31
	// 		 m a 2 252// modify EV for att to 252
	// 		 u // re-calc final stats
	};
}

Display::~Display()
{
	destroy_window(title_win);
	destroy_window(header_win);
	for (int i=0;i<7;i++) {
		destroy_window(slot[i]);
	}
	destroy_window(msg_win);
}

void Display::setTitle(string title)
{
	mvwprintw(title_win,1,1,title.c_str());
	mvwprintw(header_win, 1, (width-15)-35, " HP   ATT   DEF   SPD   SPA   SPE");
	box(title_win,0,0);
	box(header_win,0,0);
	wrefresh(header_win);
	wrefresh(title_win);
}

void Display::writeToSlot(int index, string text)
{
	mvwprintw(slot[index], 1, 1, text.c_str());
	box(slot[index],0,0);
	wrefresh(slot[index]);
}

string Display::formatStats(enum stat_t f, int *stats)
{
	int i;
	int j;
	char str[78];
	memset(str, '\0', 78);
	char base[] = "Base Stats:"; // 11
	char iv[] = "Initial Values:"; // 15
	char ev[] = "Effort Values:"; // 14
	char calcd[] = "Final Stats:"; // 12 
	string temp;
	string spaces = "   ";

	switch(f)
	{
		case BASE:
			for (i=0;i<11;i++) {str[i] = base[i];}
			break;
		case IV:
			for (i=0;i<15;i++) {str[i] = iv[i];}
			break;
		case EV:
			for (i=0;i<14;i++) {str[i] = ev[i];}
			break;
		case FINAL:
			for (i=0;i<12;i++) {str[i] = calcd[i];}
			break;
	}	

	for (i;i<44;i++) {str[i] = ' ';}

	string rv = str;

	for (j=0;j<6;j++) {
		temp = to_string(stats[j]);
		if (stats[j] < 10) { rv = rv + " ";}
		if (stats[j] < 100) { rv = rv + " ";}
		rv = rv + temp + spaces;
	}

	return rv;
}

void Display::paint(Pokemon p) 
{
	setTitle(p.name);
	writeToSlot(1,formatStats(FINAL, p.getFinalStat()));
	writeToSlot(2,formatStats(EV, p.getEV()));
	writeToSlot(3,formatStats(IV, p.getIV()));
	writeToSlot(4,formatStats(BASE, p.getBaseStat()));
}

void Display::edit(Pokemon p)
{
	bool editing = true;
	char cmd = '\0';
	paint(p);
	while (editing) {
		cmd = wgetch();	
		if (commands[cmd]) {
			commands[cmd].run();
		} else if (cmd == 'q') {
			editing = false;
		}
	}
}

void Display::wait() 
{
	wgetch(title_win);
}








WINDOW *new_window(int h, int w, int starty, int startx, bool border)
{
	WINDOW *localwin;
	localwin = newwin(h,w,starty, startx);
	wrefresh(localwin);
	return localwin;
}

void destroy_window(WINDOW *w) 
{
	delwin(w);
}
