#pragma once
#include <vector>
#include <iostream>
#include "carta.h"
#include "mesa.h"
using namespace std;

class Player {
public:

    Player() {}

    Player(const std::string& name, int chips, bool fould) : m_name(name), m_chips(chips), m_folded(fould) {}
    
    string getName() {
        return m_name;
    }
    int Bet(int amount) {
        m_chips -= amount;
        return amount;
    }
    vector<Card> GetHand() const {
        return m_hand;
    }

    string getcard(int counter) {
        return m_hand[counter].cardstring();
    }
    int GetChips() const {
        return m_chips; 
    }

    void ReceiveChips(int amount) {
        m_chips += amount;
    }

    int GetCurrentBet() const {
        return m_currentBet;
    }

    bool NeedsToMatchBet(int highestBet) const {
        return m_currentBet < highestBet;
    }

    bool WantsToCall(int highestBet) const {
        string answer;
        int counter=0;
        cout << m_name << " ";
        cout << "necesitas igualar, quieres igualaer o retirarte? si o no" << endl;
        while (counter!=1) {
            cout << "respuesta: ";
            cin >> answer;
            if ((answer == "si")or(answer=="no")) {
                counter = 1;
            }
            else {
                cout << endl << "porfavor responda usando si o no" << endl;
            }
            
        }
        if (answer == "si") {
            return true;
        }else {
            return false;
        }
        

    }
    void Fold() {
        m_folded = true;
    }
    void NotFold() {
        m_folded = false;
    }
    bool HasFolded() const {
        return m_folded;
    }
    int EvaluateHand() const {
        if (HasRoyalFlush()) {
            return 10;
        }
        else if (HasStraightFlush()) {
            return 9;
        }
        else if (HasFourOfAKind()) {
            return 8;
        }
        else if (HasFullHouse()) {
            return 7;
        }
        else if (HasFlush()) {
            return 6;
        }
        else if (HasStraight()) {
            return 5;
        }
        else if (HasThreeOfAKind()) {
            return 4;
        }
        else if (HasTwoPair()) {
            return 3;
        }
        else if (HasPair()) {
            return 2;
        }
        else {
            return 1; // High Card
        }
    }
    bool m_folded;
    int m_currentBet;
    vector<Card> m_hand;
    ~Player() {}

    
    
private:
    string m_name;
    int m_chips;
  

   bool HasRoyalFlush() const {
       return (false);
    }

    bool HasStraightFlush() const {
        return (false);
    }

    bool HasFourOfAKind() const {
        return (false); 
    }

    bool HasFullHouse() const {
        return (false);
    }

    bool HasFlush() const {
        return (false);
    }

    bool HasStraight() const {
        return (false);
    }

    bool HasThreeOfAKind() const {
        return (false);
    }

    bool HasTwoPair() const {
        return (false);
    }

    bool HasPair() const {
        return (false);
    }
};