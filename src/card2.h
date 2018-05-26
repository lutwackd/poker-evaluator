#ifndef CARD2_H
#define CARD2_H

#include <iostream>
#include <vector>

using namespace std;

enum Suit {
	heart,
	diamond,
	club,
	spade,
	invalid_suit
};

enum Rank {
	two, //0
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten, // 8
	jack,
	queen,
	king,
	ace, // 11
	invalid_rank 
};


struct Card {
	Rank current_rank;
	Suit current_suit;
	bool operator< (const Card& second_card) const {//'this' is the first card
		if (this->current_rank < second_card.current_rank) {
			return true;
		}
		if (this->current_rank > second_card.current_rank) {
			return false;
		}
		else {
			if (this->current_suit < second_card.current_suit) return true;
			else return false;
		}

	}
	bool operator== (const Card& second_card) const {//'this' is the first card
		if (this->current_rank == second_card.current_rank && this->current_suit ==  second_card.current_suit) return true;
		else return false;
	}
};

Rank Assign_Rank(char c);
Suit Assign_Suit(char c);


#endif