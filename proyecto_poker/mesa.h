#pragma once
#include <vector>
#include <iostream>
#include "jugador.h"
#include <random> 
#include <algorithm>
using namespace std;

class Table {

public:
    Table(int numPlayers) : m_numPlayers(numPlayers), m_dealerIndex(0) {
        m_players.reserve(numPlayers);
    }
    void AddPlayer(const Player & player);
    void StartGame();
    void EndGame();
    Player & GetDealer() {
        return m_players[m_dealerIndex];
    }
    string getnamedealer(Player & dealer);
    void NextDealer();
    void AutoSelectDealer();
    void DealCards();
    void DealCommunityCard();
    void MoveUsedCardsToPot();
    vector<Card> CreateDeck();
    Player DetermineWinner();
    void RemoveBankruptPlayers();
    bool EnoughActivePlayers() const;
    void PlayerBet(int betAmount);
    void AwardPotToWinner(Player & winner);
    int GetHighestBet() const {
        return m_highestBet;
    }
    void UpdateHighestBet(int newBet);
    void ResetHighestBet();
    string getNamecommunity(int counter);
    string getNameCardPlayer(int counter, Player & m_player, int view);
    bool Viewcard(int counter);
    void ActivateAllPlayers();

   
    vector<Player> m_players;
    int m_dealerIndex;
    vector<Card> m_communityCards;
    int scorehigh;
private:
    int m_numPlayers;
    int m_betAmount;
    int m_highestBet;
    Player winner;
    
    vector<Card> m_deck=CreateDeck();
    vector<Card> m_pot;
    void ShuffleDeck();

};
