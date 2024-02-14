#include "carta.h"
#include <vector>
#include <iostream>

std::string Card::cardstring() const {
    std::string suitStr;
    std::string rankStr;

    // Convertir el palo a cadena
    switch (m_suit) {
    case Suit::HEARTS: suitStr = "HEARTS"; break;
    case Suit::DIAMONDS: suitStr = "DIAMONDS"; break;
    case Suit::CLUBS:    suitStr = "CLUBS"; break;
    case Suit::SPADES:   suitStr = "SPADES"; break;
    }

    // Convertir la denominación a cadena
    switch (m_rank) {
    case Rank::ACE:   rankStr = "ACE"; break;
    case Rank::TWO:   rankStr = "TWO"; break;
    case Rank::THREE: rankStr = "THREE"; break;
    case Rank::FOUR:  rankStr = "FOUR"; break;
    case Rank::FIVE:  rankStr = "FIVE"; break;
    case Rank::SIX:   rankStr = "SIX"; break;
    case Rank::SEVEN: rankStr = "SEVEN"; break;
    case Rank::EIGHT: rankStr = "EIGHT"; break;
    case Rank::NINE:  rankStr = "NINE"; break;
    case Rank::TEN:   rankStr = "TEN"; break;
    case Rank::JACK:  rankStr = "JACK"; break;
    case Rank::QUEEN: rankStr = "QUEEN"; break;
    case Rank::KING:  rankStr = "KING"; break;
    }

    // Combinar el palo y la denominación en una cadena
    return rankStr + " " + suitStr;
}