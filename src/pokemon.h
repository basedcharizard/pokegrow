#ifndef _pokemon_h
#define _pokemon_h
#include <string>
using namespace std;

typedef enum {
	HP, ATT, DEF, SPA, SPD, SPE
} stat;

class Nature {
	public:
	string name;
	float modifiers[5]; // store modifiers here, in enum stat order
	Nature(string n);
	Nature(string n, float att, float def, float spa, float spd, float spe);	
	Nature(string n, stat inc, stat dec);
};

class Pokemon {
	int level;
	Nature *nature;
	int base_stats[6];
	int initial_values[6];
	int effort_values[6];
	int final_stats[6];

	int *calcFinalStat(int level);
	int calcFinalStat(int level, stat s);

	public:
	string name;	

	Pokemon(Nature *n);
	string getNatureString();
	Nature *getNatureObj();

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
