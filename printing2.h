#ifndef PRINTING2_H
#define PRINTING2_H

#include "card2.h"
#include "hand2.h"
#include <iostream>
#include <vector>

using namespace std;



enum usage {
	success,
	filenotopened,
	onlyshuffle, //only one command line argument is given but it contains "-shuffle".
	noshuffle,// two command line arguments are given but neither one contains "-shuffle".
	noargs, //no command line arguments are given
	toomanyargs, //more than 2 command line arguments are given
	notenoughcards //to fill hands
};





string Rank_String(Rank s);
string Suit_String(Suit s);
usage Print_Error(usage, string);
string Print_Hand_Rank(Hand_Rank hand); //Called on valid 5 card hands

#endif
