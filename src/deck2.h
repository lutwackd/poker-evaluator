#ifndef DECK2_H
#define DECK2_H

#include <iostream>
#include <vector>
#include <string>
class Hand;

using namespace std;


class Deck{
private:
	vector<Card> cards_in_deck;

public:	
	//constructor
	Deck(char* filename) { 
		load(filename);
	}

	//destructor

	void load(char* filename);
	void shuffledeck();
	int size() const {
		return cards_in_deck.size();
	}

	//friend declarations
	friend ostream& operator<< (ostream &, const Deck &);
	friend Hand& operator<< (Hand &h, Deck &d);
	

	
};

//declaration of printing operator for printing a deck 
ostream& operator<< (ostream &, const Deck &);


#endif