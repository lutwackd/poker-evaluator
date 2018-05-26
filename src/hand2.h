#ifndef HAND2_H
#define HAND2_H

#include "card2.h"
#include "deck2.h"
#include <iostream>
#include <vector>

using namespace std;

enum Hand_Rank { // 4 cases including 1 success and 3 errors
	no_rank, //0
	one_pair, //1
	two_pair, //2
	three_of_a_kind, //3
	straight, //4
	flush, //5
	full_house, //6
	four_of_a_kind, //7
	straight_flush //8
};

class Hand {
private:
	vector<Card> cards_in_hand;

	//an integer used to determine winner of two hands with the same rank. For example, if the hand ranks
	//were 4 of a kind of Aces and 4 of a kind of 9s, the "comparable" ints would be enum value "Rank :: nine" and " "Rank :: 9""
	vector<int> comparable;
	string rank;
public:
	//constructor
	Hand() {}

	// Copy constructor
	Hand(const Hand &h) { cards_in_hand = h.cards_in_hand; comparable = h.comparable; }


	//Hand_Rank current_hand_rank;
	int getSize() const {
		return cards_in_hand.size();
	}

	//getter for the comparable vector of ints
	vector<int> getComparable() const {
		return comparable;
	}
	//get the rank and assign the comparable
	Hand_Rank getRank();

	//returns string of card definition strings
	string asString() const;

	//overloaded operators
	bool operator== (Hand const&);
	bool operator< (Hand const&);
	void operator= (Hand const&);

	//friend declarations
	friend ostream& operator<< (ostream &, const Hand &);
	friend Hand& operator<< (Hand &h, Deck &d);
	friend bool poker_rank(Hand &, Hand&);

};

//printing
ostream & operator<< (ostream &, const Hand &);

//dealing

Hand& operator<< (Hand &h, Deck &d);

//comparing ranks of two hands

bool poker_rank(Hand&, Hand& );

#endif