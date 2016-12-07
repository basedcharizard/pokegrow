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
	err_win = new_window(height, width, 0, 0, false);
}

Display::~Display()
{
	destroy_window(title_win);
	destroy_window(header_win);
	for (int i=0;i<7;i++) {
		destroy_window(slot[i]);
	}
	destroy_window(err_win);
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
	char calcd[] = "Final Stats:"; // 15
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
			for (i=0;i<15;i++) {str[i] = calcd[i];}
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

void Display::edit(Pokemon p)
{
	setTitle(p.name);
	writeToSlot(1,formatStats(BASE, p.getBaseStat()));
	writeToSlot(2,formatStats(IV, p.getIV()));
	writeToSlot(3,formatStats(EV, p.getEV()));
	writeToSlot(4,formatStats(FINAL, p.getFinalStat()));
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
