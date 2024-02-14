#include "mesa.h"

// Función para agregar un jugador a la mesa
void Table::AddPlayer(const Player& player) {
    m_players.push_back(player);
}

// Función para iniciar el juego
void Table::StartGame() {
    DealCards();
    DealCommunityCard();
    m_dealerIndex = 0; // Establecer el primer jugador como el dealer inicial
}

void Table::EndGame() {
    winner=DetermineWinner();
    AwardPotToWinner(winner); 
    MoveUsedCardsToPot();
    RemoveBankruptPlayers();
    ResetHighestBet();
}

void Table::NextDealer() {
    m_dealerIndex = (m_dealerIndex + 1) % m_numPlayers;
}


void Table::AutoSelectDealer() {
    NextDealer();
}


void Table::DealCards() {
    // Barajar el mazo antes de repartir las cartas
    ShuffleDeck();
    int repetir = 0;
    for (repetir=0;repetir<=2;repetir++)
    for (auto& player : m_players) {
        player.m_hand.push_back(m_deck.back());
        m_deck.pop_back();
    }
}


void Table::DealCommunityCard() {
    // Si el mazo principal está vacío, mover las cartas del pozo al mazo y barajarlas
    if (m_deck.empty()) {
        m_deck = m_pot; // Mover las cartas del pozo al mazo
        m_pot.clear(); // Limpiar el pozo
        ShuffleDeck(); // Barajar las cartas en el mazo
    }

    // Repartir una carta comunitaria
    m_communityCards.push_back(m_deck.back());
    m_deck.pop_back();
}
//crea las 52 cartas 
vector<Card> Table::CreateDeck() {
    std::vector<Card> deck;

    for (int s = static_cast<int>(Card::Suit::HEARTS); s <= static_cast<int>(Card::Suit::SPADES); ++s) {
        for (int r = static_cast<int>(Card::Rank::ACE); r <= static_cast<int>(Card::Rank::KING); ++r) {
            Card card(static_cast<Card::Suit>(s), static_cast<Card::Rank>(r));
            deck.push_back(card);
        }
    }

    return deck;
}

void Table::ShuffleDeck() {
    std::random_device rd;
    std::mt19937 rng(rd());

    // Usamos el algoritmo de barajado Fisher-Yates
    std::shuffle(m_deck.begin(), m_deck.end(), rng);
}

Player Table::DetermineWinner() {
    int maxScore = 0;
    Player winningPlayer;

    // Iterar sobre cada jugador y evaluar su mano
    for (size_t i = 0; i < m_players.size(); ++i) {
        int playerScore = m_players[i].EvaluateHand();
        if (playerScore > maxScore) {
            maxScore = playerScore;
            winningPlayer = m_players[i];
        }
    }

    return winningPlayer;
}

void Table::MoveUsedCardsToPot() {
    // Mover las cartas de la mano de los jugadores al pozo
    for (auto& player : m_players) {
        for (const auto& card : player.m_hand) {
            m_pot.push_back(card);
        }
        player.m_hand.clear();
    }

    // Mover las cartas comunitarias al pozo
    for (const auto& card : m_communityCards) {
        m_pot.push_back(card);
    }
    m_communityCards.clear();
}

void Table::RemoveBankruptPlayers() {
    auto it = std::remove_if(m_players.begin(), m_players.end(), [](const Player& player) {
        return player.GetChips() <= 0; // Verifica si el jugador tiene créditos iguales o menores que cero

        });

    m_players.erase(it, m_players.end()); // Elimina a los jugadores sin créditos de la lista
}

bool Table:: EnoughActivePlayers() const {
    if (m_players.size() >= 2) {// Verifica si hay al menos dos jugadores activos
        return true;
    }
    else {
     return false;
    }

     
}
void Table::PlayerBet(int betAmount) {
    m_betAmount += betAmount; // Agrega la cantidad apostada al total en la mesa
    UpdateHighestBet(betAmount);
    m_players[m_dealerIndex].m_currentBet = betAmount;
}

void Table::AwardPotToWinner(Player& winner) {
    winner.ReceiveChips(m_betAmount); // El ganador recibe la cantidad apostada
    m_betAmount = 0; // Reinicia el monto apostado en la mesa para la próxima ronda
}

void Table::UpdateHighestBet(int newBet) {
    if (newBet > m_highestBet) {
        m_highestBet = newBet;
    }
}

void Table::ResetHighestBet() {
    m_highestBet = 0;
}

string Table::getnamedealer(Player& dealer) {
    return dealer.getName();
}

string Table::getNamecommunity(int counter) {
    string namecard;
    if (counter >= 0 && counter < m_communityCards.size()) {
        namecard = m_communityCards[counter].cardstring()+".png";
    }
    else {
        namecard = "tracera.png";
    }
    return namecard;
}

string Table::getNameCardPlayer(int counter, Player& m_player, int view) {

    string namecard;
    if (Viewcard(view) == true && counter >= 0 && counter < m_player.getcard(counter).size()) {
        namecard = m_player.getcard(counter) + ".png";
    }
    else {
        namecard = "tracera.png";
    }
    return namecard;
}

bool Table::Viewcard(int counter) {
    if (counter == 1) {
        return true;
    }
    else if (counter == 2) {
        return false;
    }
}
void Table::ActivateAllPlayers() {
    for (auto& player : m_players) {
        player.NotFold(); // Llama a la función NotFold() para cada jugador
    }
}