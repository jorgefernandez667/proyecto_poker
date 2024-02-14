#pragma once
#include <iostream>


class Card {
public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
    enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

    Card(Suit suit, Rank rank) : m_suit(suit), m_rank(rank) {}
    std::string cardstring() const;
    
private:
    Suit m_suit;
    Rank m_rank;
   
};