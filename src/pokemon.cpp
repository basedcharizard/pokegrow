#include "pokemon.h"

Nature::Nature(string n) {
	name = n;
	modifiers[0] = 1;
	modifiers[1] = 1;
	modifiers[2] = 1;
	modifiers[3] = 1;
	modifiers[4] = 1;
}

Nature::Nature(string n, float att, float def, float spa, float spd, float spe) {
	name = n;
	modifiers[0] = att;
	modifiers[1] = def;
	modifiers[2] = spa;
	modifiers[3] = spd;
	modifiers[4] = spe;
}

Nature::Nature(string n, stat inc, stat dec) {
	name = n;
	for (int i=0;i<5;i++) {
		if (inc == (i+1)) {modifiers[i] = 1.1;}
		else if (dec == (i+1)) {modifiers[i] = 0.9;}
		else {modifiers[i] = 1;}
	}
}

Pokemon::Pokemon(Nature *n) {
	name = "Garchomp";
	level = 100;
	nature = n;
	base_stats[HP] = 108;
	base_stats[ATT] = 130;
	base_stats[DEF] = 95;
	base_stats[SPA] = 80;
	base_stats[SPD] = 85;
	base_stats[SPE] = 102;

	initial_values[HP] = 31;
	initial_values[ATT] = 31;
	initial_values[DEF] = 31;
	initial_values[SPA] = 31;
	initial_values[SPD] = 31;
	initial_values[SPE] = 31;

	effort_values[HP] = 0;
	effort_values[ATT] = 0;
	effort_values[DEF] = 0;
	effort_values[SPA] = 0;
	effort_values[SPD] = 0;
	effort_values[SPE] = 0;
	
	final_stats[HP] = 0;
	final_stats[ATT] = 0;
	final_stats[DEF] = 0;
	final_stats[SPA] = 0;
	final_stats[SPD] = 0;
	final_stats[SPE] = 0;
}

string Pokemon::getNatureString(){return nature->name;}
Nature *Pokemon::getNatureObj(){return nature;}
void Pokemon::setLevel(int lvl) {level = lvl;}
int Pokemon::getLevel() {return level;}

int *Pokemon::getBaseStat() { return base_stats;}
int Pokemon::getBaseStat(stat s) { return base_stats[s];}

int *Pokemon::getIV(){ return initial_values;}
int Pokemon::getIV(stat s){ return initial_values[s];}
void Pokemon::setIV(stat s, int v){
	initial_values[s] = v;
}


int *Pokemon::getEV() { return effort_values;}
int Pokemon::getEV(stat s) { return effort_values[s];}
void Pokemon::setEV(stat s, int v) {
	effort_values[s] = v;
}

int *Pokemon::getFinalStat() {calcFinalStat(level); return final_stats;}
int Pokemon::getFinalStat(stat s) {calcFinalStat(level); return final_stats[s];}

int *Pokemon::calcFinalStat(int level) {
	for (int i=0; i<6; i++) {
		if (i==0) {
			final_stats[i] = (((2*base_stats[i]+initial_values[i]+(effort_values[i]/4))*level)/100)+level+10;
		} else {
			final_stats[i] = ((((2*base_stats[i]+initial_values[i]+(effort_values[i]/4))*level)/100)+5)*nature->modifiers[i-1];
		}		
	}
	return final_stats;
}

int Pokemon::calcFinalStat(int level, stat s) {
	if (s == HP) {
		return 69;
	} else {
		return (((2*base_stats[s]+initial_values[s]+(effort_values[s]/4))*level)/100)+5;
 	}
}
