#ifndef _pokemon_h
#define _pokemon_h
#include <string>
using namespace std;

typedef enum {
	HP, ATT, DEF, SPD, SPA, SPE
} stat;

class Pokemon {
	int level;
	int base_stats[6];
	int initial_values[6];
	int effort_values[6];
	int final_stats[6];

	int *calcFinalStat(int level);
	int calcFinalStat(int level, stat s);

	public:
	string name;	

	Pokemon();
	void setLevel(int lvl);
	int getLevel();

	int *getBaseStat();
	int getBaseStat(stat s);

	int *getIV();
	int getIV(stat s);
	void setIV(stat s, int v);

	int *getEV();
	int getEV(stat s);
	void setEV(stat s, int v);

	int *getFinalStat();
	int getFinalStat(stat s);
};

#endif
