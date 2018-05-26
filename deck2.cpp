#include "stdafx.h"
#include "printing2.h"
#include "card2.h"
#include "hand2.h"
#include "deck2.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <random>
using namespace std;

//function that parses file and adds all valid strings to a deck. Also prints an error message for each inv. card
void
Deck :: load(char* filename) {

		ifstream file(filename);
		if (file.is_open()) {

			string line;
			string entry;
			while (getline(file, line)) {//while there is a still a line to be read
				istringstream iss(line);//getting the line;
				bool comment = false;
				while ((iss >> entry) && !comment) { // while theres still an entry to be read
					bool valid = false;
					if (entry.find("//") != string::npos) {
						comment = true;
						entry.resize(entry.find("//"));
					}

					int s = entry.size();
					if (s == 2 || s == 3) {

						if (s == 2) {// 2 char entry
							bool is_correct_last = false;
							bool is_correct_first = false;

							//suit
							int last = ((int)entry[1]) | 32;//making last character lowercase to make case insensitive
							if (last == 'c' || last == 'd' || last == 'h' || last == 's') {
								is_correct_last = true;
							}

							//rank
							int facecard = ((int)entry[0]) | 32;
							if ((entry[0] > 49 && entry[0] < 58) || facecard == 'j' || facecard == 'q'
								|| facecard == 'k' || facecard == 'a') {
								is_correct_first = true;//true if card is 2-9 or jqka
							}

							//if it was a valid card
							if (is_correct_first && is_correct_last) {
								Card successful;
								successful.current_rank = Assign_Rank(entry[0]); //assign rank
								successful.current_suit = Assign_Suit(entry[1]); //assign suit
								cards_in_deck.push_back(successful); //add to deck
								valid = true;
							}
						}  //2 card entry validation

						if (s == 3) { // 3 char entry - (first 2 chars be 1 and 0
							bool is_correct_last = false;

							//if the last character is correct, set boolean true
							int last = ((int)entry[2]) | 32;
							if (last == 'c' || last == 'd' || last == 'h' || last == 's') is_correct_last = true;

							// if its a valid card
							if (entry[0] == '1' && entry[1] == '0' && is_correct_last) {//checking that all 3 characters are valid 
								Card successful;
								successful.current_rank = Assign_Rank(entry[0]); //assign rank
								successful.current_suit = Assign_Suit(entry[2]); //assign suit
								cards_in_deck.push_back(successful); //add to deck
								valid = true;
							}
						} 
					}
					if (!valid) {
						cout << "Warning: invalid card string found. Program continued to parse ";
						cout << "data and ignored invalid strings. " << endl;
					}
				}

				
			}
			if (cards_in_deck.size() == 0) throw notenoughcards;
			cout << "" << endl;
		}
		else throw filenotopened; //if the file couldnt open return 
	
}

void
Deck::shuffledeck() {
	//from en.cppreference.com/w/cpp/algorithm/random_shuffle
	random_device rd;
	mt19937 g(rd());
	shuffle(cards_in_deck.begin(), cards_in_deck.end(), g);
}

//definition of the << operator - used to print out all the cards in a deck object
ostream& operator<< (ostream &o, const Deck &d) {
	for (int i = 0; i < d.size(); i++) {

		string rankstring = to_string(d.cards_in_deck[i].current_rank + 2);
		if (rankstring == "11") rankstring = "J";
		if (rankstring == "12") rankstring = "Q";
		if (rankstring == "13") rankstring = "K";
		if (rankstring == "14") rankstring = "A";
		string suitstring = to_string(d.cards_in_deck[i].current_suit);
		if (suitstring == "0") suitstring = "H";
		if (suitstring == "1") suitstring = "D";
		if (suitstring == "2") suitstring = "C";
		if (suitstring == "3") suitstring = "S";
		cout << rankstring;
		cout << suitstring << " ";
		if (i % 10 == 9) cout << "\n" << endl;
		
	}
	return o;
}


