#include "stdafx.h"
#include "printing2.h"
#include "card2.h"
#include "hand2.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string Rank_String(Rank r) {
	if (r == two) return "Two";
	if (r == three) return "Three";
	if (r == four) return "Four";
	if (r == five) return "Five";
	if (r == six) return "Six";
	if (r == seven) return "Seven";
	if (r == eight) return "Eight";
	if (r == nine) return "Nine";
	if (r == ten) return "Ten";
	if (r == jack) return "Jack";
	if (r == queen) return "Queen";
	if (r == king) return "King";
	if (r == ace) return "Ace";
	if (r == invalid_rank) return "Invalid Rank";
	return "Invalid Rank";
}

string Suit_String(Suit s) {
	if (s == heart) return "Hearts";
	if (s == diamond) return "Diamonds";
	if (s == club) return "Clubs";
	if (s == spade) return "Spades";
	if (s == invalid_suit) return "Invalid Suit";
	return "Invalid Suit";
}

string Print_Hand_Rank(Hand_Rank rank) {
	if (rank == one_pair) return  "One Pair";
	if (rank == two_pair) return  "Two Pair";
	if (rank == three_of_a_kind) return  "Three of a Kind";
	if (rank == straight) return  "Straight";
	if (rank == Hand_Rank::flush) return  "Flush";
	if (rank == full_house) return  "Full House";
	if (rank == four_of_a_kind) return  "Four of a Kind";
	if (rank == straight_flush) return  "Straight Flush";
	return "High Card";
}


usage Print_Error(usage code, string program_name) {
	switch (code) {
	
	case filenotopened: 
		cout << "\nIncorrect usage of " << program_name << endl;
		cout << "Your file was not able to be opened. Make sure to include the" << endl;
		cout << ".txt extension and to call it as your second or third  argument "<< endl;
		cout << "after the executable. For exampe: LabTwo.exe cards.txt -shuffle" << endl;
		return filenotopened;

	case onlyshuffle: 
		cout << "\nIncorrect usage of " << program_name << endl;
		cout << "Only one command line argument '-shuffle' was entered. Make" << endl;
		cout << "sure to also include a text file. Your command should appear as: "<< endl;
		cout << "LabTwo.exe cards.txt -shuffle (shuffle is optional)" << endl;
		return onlyshuffle;

	case noshuffle:
		cout << "\nIncorrect usage of " << program_name << endl;
		cout << "Two command line arguments were given but neither contained " << endl;
		cout << " '-shuffle'. Make sure your command follows the example: " << endl;
		cout << "LabTwo.exe cards.txte -shuffle (shuffle is optional)"<< endl;
		return noshuffle;

	case noargs: 
		cout << "\nIncorrect usage of " << program_name << endl;
		cout << "Not enough command line arguments were given. Please make " << endl;
		cout << "sure to follow this example: LabTwo.exe, cards.txt, -shuffle " << endl;
		cout << "(shuffle is optional)" << endl;
		return noargs;
	case toomanyargs: 
		cout << "\nIncorrect usage of " << program_name << endl;
		cout << "Too many command line arguments were supplied. This program " << endl;
		cout << "can accept at most 3. Be sure to follow this example: " << endl;
		cout << "LabTwo.exe, cards.txt, -shuffle (shuffle is optional)" << endl;
		return toomanyargs;

	case notenoughcards: 
		cout << "\nIncorrect usage of " << program_name << endl;
		cout << "Not enough cards were supplied to fill all 9 hands. This " << endl;
		cout << "program requires at minimum 45 valid card strings. Please " << endl;
		cout << "ensure card strings are valid or add more if necessary" << endl;
		return notenoughcards;


	default:
		return success; //note -- NEVER used 
	}

}