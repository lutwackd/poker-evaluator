#include "stdafx.h"
#include "printing2.h"
#include "hand2.h"
#include "card2.h"
#include "deck2.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;


//returns the rank of a given hand
Hand_Rank Hand::getRank() {

	comparable.clear();// clears the comparables before redoing them below
		
	sort(this->cards_in_hand.begin(), this->cards_in_hand.end());

	bool is_straight = true;
	bool is_flush = true;
	bool is_four_of_kind = false;
	bool is_full_house = false;
	bool is_three_of_kind = false;
	bool is_pair = false;
	bool is_two_pair = false;

	int comparable1;
	int comparable2;
	int comparable3;


	//STRAIGHT TEST
	for (int i = 0; i < getSize() - 1; i++) {
		if (cards_in_hand[i].current_rank + 1 != cards_in_hand[i + 1].current_rank) is_straight = false;
	}
	//SPECIAL straight test for A2345;
	if (cards_in_hand[getSize() - 1].current_rank == ace && cards_in_hand[0].current_rank == two) {
		is_straight = true;
		for (int i = 0; i < getSize() - 2; i++) {
			if (cards_in_hand[i].current_rank + 1 != cards_in_hand[i + 1].current_rank) is_straight = false;
		}
	}
	//FLUSH TEST
	for (int i = 0; i < getSize() - 1; i++) {
		if (cards_in_hand[i].current_suit != cards_in_hand[i + 1].current_suit) is_flush = false;
	}


	//FOUR OF A KIND TEST
	//booleans for if either of the two possible locations for a four of a kind (0-3) and (1-4) are filled with equal rank cards
	bool four_cards_same_1 = ((cards_in_hand[1].current_rank == cards_in_hand[2].current_rank) && (cards_in_hand[2].current_rank ==
		cards_in_hand[3].current_rank) && (cards_in_hand[3].current_rank == cards_in_hand[4].current_rank));
	bool four_cards_same_2 = ((cards_in_hand[0].current_rank == cards_in_hand[1].current_rank) && (cards_in_hand[1].current_rank ==
		cards_in_hand[2].current_rank) && (cards_in_hand[2].current_rank == cards_in_hand[3].current_rank));
	if (four_cards_same_1 || four_cards_same_2)  is_four_of_kind = true; // if a four of a kind is present 


																		 //three of a kind and full HOUSE TEST
	bool first_three_same = (cards_in_hand[0].current_rank == cards_in_hand[1].current_rank && cards_in_hand[1].
		current_rank == cards_in_hand[2].current_rank);
	bool last_three_same = (cards_in_hand[2].current_rank == cards_in_hand[3].current_rank && cards_in_hand[3].
		current_rank == cards_in_hand[4].current_rank);
	bool three_mid_same = (cards_in_hand[1].current_rank == cards_in_hand[2].current_rank && cards_in_hand[2].
		current_rank == cards_in_hand[3].current_rank);
	bool first_two_same = (cards_in_hand[0].current_rank == cards_in_hand[1].current_rank);
	bool last_two_same = (cards_in_hand[3].current_rank == cards_in_hand[4].current_rank);

	if (first_three_same || three_mid_same || last_three_same) is_three_of_kind = true;
	if (first_three_same && last_two_same) is_full_house = true;
	if (first_two_same && last_three_same) is_full_house = true;

	//pair test
	int loc;
	int pairedvalue; //will become the comparable for single pairs
	for (int i = 0; i < getSize() - 1; i++) {
		if (cards_in_hand[i].current_rank == cards_in_hand[i + 1].current_rank) {
			pairedvalue = cards_in_hand[i].current_rank;
			loc = i;
			is_pair = true;
		}
	}


	//two-pair test 
	bool next_two_same = (cards_in_hand[2].current_rank == cards_in_hand[3].current_rank); //2 and 3 spot
	bool prev_two_same = (cards_in_hand[1].current_rank == cards_in_hand[2].current_rank); //1 and 2 spot

	if (first_two_same && next_two_same) is_two_pair = true;
	if (last_two_same && prev_two_same) is_two_pair = true;
	if (first_two_same && last_two_same) is_two_pair = true;

	if (is_four_of_kind) {
		comparable1 = cards_in_hand[2].current_rank; //third card is by necessarily the matched card because hand is ordered
		comparable.push_back(comparable1); //adds the matched 4 of a kind rank to the comparable
		return four_of_a_kind;
	}
	if (is_flush && is_straight) {
		comparable1 = cards_in_hand[4].current_rank;
		comparable.push_back(comparable1);
		return straight_flush;
	}
	if (is_full_house) {
		comparable1 = cards_in_hand[2].current_rank;
		if (comparable1 == cards_in_hand[4].current_rank) {
			comparable2 = cards_in_hand[0].current_rank;
		}
		else comparable2 = cards_in_hand[4].current_rank;
		comparable.push_back(comparable1);
		comparable.push_back(comparable2);
		return full_house;
	}
	if (is_flush) {
		for (int i = getSize() - 1; i >= 0; i--) {
			comparable.push_back(cards_in_hand[i].current_rank);
		}
		return Hand_Rank::flush;
	}
	if (is_straight) {
		comparable1 = cards_in_hand[4].current_rank;
		comparable.push_back(comparable1);
		return straight;
	}
	if (is_three_of_kind) {
		comparable1 = cards_in_hand[2].current_rank; //matched card MUST be in that position
		comparable.push_back(comparable1);
		return three_of_a_kind;
	}
	if (is_two_pair) {

		int match1; //one of the two pairs (higher will be determined later
		int match2;// the second pair
		int kicker; // the other card

		if (first_two_same && last_two_same) {
			match1 = cards_in_hand[0].current_rank;
			match2 = cards_in_hand[4].current_rank;
			kicker = cards_in_hand[2].current_rank;
		}

		if (first_two_same && next_two_same) {
			match1 = cards_in_hand[0].current_rank;
			match2 = cards_in_hand[2].current_rank;
			kicker = cards_in_hand[4].current_rank;
		}
		if (last_two_same && prev_two_same) {
			match1 = cards_in_hand[4].current_rank;
			match2 = cards_in_hand[2].current_rank;
			kicker = cards_in_hand[0].current_rank;
		}

		if (match1 > match2) { //assigning the higher matched pair to be the first element in comparable vector
			comparable1 = match1;
			comparable2 = match2;
			comparable3 = kicker;
		}
		else {
			comparable1 = match2;
			comparable2 = match1;
			comparable3 = kicker;
		}

		comparable.push_back(comparable1);
		comparable.push_back(comparable2);
		comparable.push_back(comparable3);


		return two_pair;
	}




	if (is_pair) {
		comparable1 = pairedvalue;
		comparable.push_back(comparable1);
	//	loc loc and loc+1 are the pair
			for (int i = getSize() - 1; i >= 0;i--) {
				if ((i != loc)  && (i != loc + 1)) {
					comparable.push_back(cards_in_hand[i].current_rank);
				}
			}

		return one_pair;
	}

	//otherwise...

	for (int i = getSize() - 1; i >= 0;i--) {
		comparable.push_back(cards_in_hand[i].current_rank);
	}


	return no_rank;



}


// == operator for hand
bool
Hand :: operator== (Hand const& other) {
	if (this->getSize() != other.getSize()) return false;
	else {
		for (int i = 0; i < other.getSize(); i++) {
			if (!(cards_in_hand[i] == other.cards_in_hand[i])) return false;
		}
	}
	return true;
}

/*A const less than operator that takes a reference to a const object of the same type and returns
true if and only if the sequence of cards in the object on which the operator was called
should appear before the sequence of cards in the passed object according to a lexical(phone book style)
ordering, based on the cards' less-than operator (hint: since cards are stored in sorted order (see the insertion
operator below which moves a card from a deck to a hand), implementing this is straight forward - compare the first
card in each hand and if they are the same compare the second card, etc.; the ordering of the first cards that differ
determines the ordering of the hands with the caveat that a hand whose cards are a prefix of the sequence of another
hand's cards should be placed earlier, e.g. "9H" before "9H 10H").*/

bool
Hand:: operator< (Hand const& other) {
	int min_size = min(getSize(), other.getSize());
	for (int i = 0; i < min_size; i++) {
		if (this->cards_in_hand[i] < other.cards_in_hand[i]) return true;
		if (other.cards_in_hand[i] < this->cards_in_hand[i]) return false;
	}
	//they are equal at this point

	if (min_size == getSize() && min_size != other.getSize()) {
		return true; // because that means the other one is longer
	}
	else {
		return false;
	}
}

string
Hand::asString() const {
	string final = "";
	for (int i = 0; i < getSize(); i++) {
		string rankstring = to_string(cards_in_hand[i].current_rank + 2);
		if (rankstring == "11") rankstring = "J";
		if (rankstring == "12") rankstring = "Q";
		if (rankstring == "13") rankstring = "K";
		if (rankstring == "14") rankstring = "A";
		string suitstring = to_string(cards_in_hand[i].current_suit);
		if (suitstring == "0") suitstring = "H";
		if (suitstring == "1") suitstring = "D";
		if (suitstring == "2") suitstring = "C";
		if (suitstring == "3") suitstring = "S";
		final += rankstring;
		final += suitstring + " ";
	}
	return final;
}

//<< printing a hand
ostream & operator<< (ostream &o, const Hand &h) {
	cout << h.asString();
	return o;
}

//A non - member insertion operator (operator<<) that takes a reference to a
//hand object and a reference to a deck object, removes the card from the back 
//of the deck object's container member variable, and adds it to the hand object's 
//container member variable in such a manner that the cards in the hand object are
//kept in sorted order(according to the card's less than operator). Note that depending
//on which STL container you used, either pushing back and then sorting (e.g., for
//vector or list) or iterating until the right spot is reached and then inserting
//(e.g., for list but not vector since that would result in an inefficient re-
//copying of stored values) are reasonable approaches. Note that your implementation 
//may use friend declarations to grant this operator access to the hand object's and deck 
//object's private member variables.

Hand& operator<< (Hand &h, Deck &d) {
	Card removing = d.cards_in_deck[d.size() - 1];
	d.cards_in_deck.pop_back(); //actual removal
	h.cards_in_hand.push_back(removing);
	sort(h.cards_in_hand.begin(), h.cards_in_hand.end());
	return h;
}


//assignment operator
void 
Hand :: operator= (Hand const& other) {
	if (rank != other.rank) rank = other.rank;
	if (comparable != other.comparable) comparable = other.comparable;
	if (cards_in_hand != other.cards_in_hand) cards_in_hand = other.cards_in_hand  ;
	
}

//
//Declare and define a "poker_rank" function that takes two references to const hand objects and returns a 
//bool value that is true if (and only if) the first hand object ranks higher than the second hand object in 
//the poker hand ranking definition given in the extra credit portion of the previous lab assignment.

bool poker_rank(Hand & first, Hand& second) {
	if (first.getRank() > second.getRank()) {
		return true;
	}
	if (first.getRank() < second.getRank()) {
		return false;
	}
	if (first.getRank() == second.getRank()) {
		for (unsigned int i = 0; i < first.comparable.size(); i++) {//size of comparables are same because rank same
			if (first.comparable[i] > second.comparable[i]) return true;
			if (first.comparable[i] < second.comparable[i]) return false;
		}
	}
	return false;

}


