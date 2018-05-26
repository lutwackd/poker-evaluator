#include "stdafx.h"
#include "card2.h"
#include "printing2.h"
#include "hand2.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


Rank Assign_Rank(char c) {
	if (c == '2') return two;
	if (c == '3') return three;
	if (c == '4') return four;
	if (c == '5') return five;
	if (c == '6') return six;
	if (c == '7') return seven;
	if (c == '8') return eight;
	if (c == '9') return nine;
	if (c == '1') return ten; //the only time where the first char of a successfully read card is 1: the rank is 10;
	if (c == 'j') return jack;
	if (c == 'q') return queen;
	if (c == 'k') return king;
	if (c == 'a') return ace;
	if (c == 'J') return jack;
	if (c == 'Q') return queen;
	if (c == 'K') return king;
	if (c == 'A') return ace;
	return invalid_rank;
}

Suit Assign_Suit(char c) {
	if (c == 'h') return heart;
	if (c == 'd') return diamond;
	if (c == 'c') return club;
	if (c == 's') return spade;
	if (c == 'H') return heart;
	if (c == 'D') return diamond;
	if (c == 'C') return club;
	if (c == 'S') return spade;
	return invalid_suit;
}
