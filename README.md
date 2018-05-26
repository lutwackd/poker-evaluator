# Overview

* This is a poker-hand evaluation tool in C++ 
* Includes card, hand, and deck classes and methods for sorting and comparing cards and hands
* Can serve as base code for multiplayer, poker-style games in C++

### Deal example

* Deck d("allcards.txt") //all.cards.txt contains AH, 2H, 3H ... QS, KS
* Hand h;
* h << d << d; // deals two cards to h

### Hand rank comparison example 

* Hand one;
* Hand two;
* one << d << d << d << d << d;
* two << d << d << d << d << d;
* cout << poker_rank(one, two); // true if hand 'one' ranks less in poker to hand 'two'
* sort(v.begin, v.end(), poker_rank) //sorts a vector of hands by their ranking

### Lexical comparison example

* Hand one;
* Hand two;
* one << d << d << d << d << d;
* two << d << d << d << d << d;
* cout << (one < two) ; // true if hand 'one' comes before 'two' in a dictionary ordering
* sort(v.begin(), v.end()) //sorts a vector of hands by dictionary ordering
