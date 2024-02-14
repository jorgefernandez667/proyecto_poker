#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "mesa.h"
void drawCard(sf::RenderWindow& window, string namecard, const sf::Vector2f& position) {
    sf::Texture texturecard;
    texturecard.loadFromFile(namecard);
    sf::Sprite cardSprite(texturecard);
    cardSprite.setPosition(position);
    cardSprite.setScale(0.5f, 0.5f);
    window.draw(cardSprite);
}

void drawButton(sf::RenderWindow& window, const sf::RectangleShape& button, const sf::Text& buttonText) {
    window.draw(button);
    window.draw(buttonText);
}
int main() {
    Table mesa(4);
    mesa.AddPlayer(Player("andres", 500, false));
    mesa.AddPlayer(Player("dalila", 500, false));
    mesa.AddPlayer(Player("oliver", 500, false));
    mesa.AddPlayer(Player("jorge", 500, false));

    // Crear una ventana SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Omaha Hi");

    // Cargar la imagen de la mesa
    sf::Texture tableTexture;
    if (!tableTexture.loadFromFile("mesa de poker.jpg")) {
        // Manejar el caso en que la carga de la imagen falle
        std::cerr << "Error al cargar la imagen de la mesa" << std::endl;
        return 1;
    }
    sf::Vector2u windowSize = window.getSize();
    // Crear un sprite para la imagen de la mesa
    sf::Sprite tableSprite;
    tableSprite.setTexture(tableTexture);
    tableSprite.setScale(static_cast<float>(windowSize.x) / tableTexture.getSize().x,
        static_cast<float>(windowSize.y) / tableTexture.getSize().y);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return 1;
    }
    // Crear texto para el botón +10
    sf::Text textAdd10("+10", font);
    textAdd10.setCharacterSize(24); // Tamaño del texto
    textAdd10.setFillColor(sf::Color::Black); // Color del texto
    textAdd10.setPosition(70, 60); // Posición del texto

    // Crear texto para el botón +5
    sf::Text textAdd5("+5", font);
    textAdd5.setCharacterSize(24); // Tamaño del texto
    textAdd5.setFillColor(sf::Color::Black); // Color del texto
    textAdd5.setPosition(70, 160); // Posición del texto

    // Crear botón para sumar 10
    sf::RectangleShape addButton10(sf::Vector2f(100, 50)); // Tamaño del botón
    addButton10.setPosition(50, 50); // Posición del botón
    addButton10.setFillColor(sf::Color::Green); // Color del botón

    // Crear botón para sumar 5
    sf::RectangleShape addButton5(sf::Vector2f(100, 50)); // Tamaño del botón
    addButton5.setPosition(50, 150); // Posición del botón
    addButton5.setFillColor(sf::Color::Blue); // Color del botón

    // Crear botón para pasar el turno
    sf::RectangleShape passButton(sf::Vector2f(100, 50)); // Tamaño del botón
    passButton.setPosition(50, 250); // Posición del botón
    passButton.setFillColor(sf::Color::Red); // Color del botón

    // Crear texto para el botón de pasar turno
    sf::Text textPass("Pass", font);
    textPass.setCharacterSize(24); // Tamaño del texto
    textPass.setFillColor(sf::Color::Black); // Color del texto
    textPass.setPosition(70, 260); // Posición del texto

   
    sf::RectangleShape retireButton(sf::Vector2f(100, 50)); // Tamaño del botón
    retireButton.setPosition(50, 450); // Posición del botón
    retireButton.setFillColor(sf::Color::Yellow); // Color del botón

  
    sf::Text textretire("retire", font);
    textretire.setCharacterSize(24); // Tamaño del texto
    textretire.setFillColor(sf::Color::Black); // Color del texto
    textretire.setPosition(70, 460); // Posición del texto

    sf::RectangleShape allButton(sf::Vector2f(100, 50)); // Tamaño del botón
    allButton.setPosition(50, 350); // Posición del botón
    allButton.setFillColor(sf::Color::Yellow); // Color del botón

    sf::Text textall("all", font);
    textall.setCharacterSize(24); // Tamaño del texto
    textall.setFillColor(sf::Color::Black); // Color del texto
    textall.setPosition(70, 360); // Posición del texto

    sf::RectangleShape viewButton(sf::Vector2f(100, 50)); // Tamaño del botón
    viewButton.setPosition(680, 540); // Posición del botón
    viewButton.setFillColor(sf::Color::Yellow); // Color del botón


    sf::Text textview("View", font);
    textview.setCharacterSize(24); // Tamaño del texto
    textview.setFillColor(sf::Color::Black); // Color del texto
    textview.setPosition(700, 550); // Posición del texto

    string playername = mesa.getnamedealer(mesa.GetDealer());

    sf::RectangleShape viewName(sf::Vector2f(200, 50)); // Tamaño del botón
    viewName.setPosition(300, 30); // Posición del botón
    viewName.setFillColor(sf::Color::White); // Color del botón

    sf::Text textName(playername, font);
    textName.setCharacterSize(24); // Tamaño del texto
    textName.setFillColor(sf::Color::Black); // Color del texto
    textName.setPosition(320, 40); // Posición del texto

    sf::RectangleShape viewChips(sf::Vector2f(170, 50)); // Tamaño del botón
    viewChips.setPosition(550, 30); // Posición del botón
    viewChips.setFillColor(sf::Color::Magenta); // Color del botón

    string chips ="budget: " + to_string(mesa.m_players[mesa.m_dealerIndex].GetChips());
    sf::Text textChips(chips, font);
    textChips.setCharacterSize(24); // Tamaño del texto
    textChips.setFillColor(sf::Color::Black); // Color del texto
    textChips.setPosition(570, 40); // Posición del texto

    int counter = 0;
    int view = 2;
    mesa.StartGame();
    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        
       if (mesa.m_players[mesa.m_dealerIndex].HasFolded()) {
            mesa.NextDealer();
            counter++;
        }
        
        while (window.pollEvent(event)) {
           
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
              
                if (event.mouseButton.button == sf::Mouse::Left &&addButton10.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (mesa.GetHighestBet() <= 10) {
                        mesa.PlayerBet(mesa.m_players[mesa.m_dealerIndex].Bet(10));
                        mesa.NextDealer();
                        counter++;
                    }
                    else {
                        cout << "tienes que apostar mas de 10" << endl;
                    }
                    cout << "la apuesta mas alta es de: " << mesa.GetHighestBet() << endl;
                }
                else if (event.mouseButton.button == sf::Mouse::Left && addButton5.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (mesa.GetHighestBet() <= 5) {
                        mesa.PlayerBet(mesa.m_players[mesa.m_dealerIndex].Bet(5));
                        mesa.NextDealer();
                        counter++;
                    }
                    else {
                        cout << "tienes que apostar mas de 5" << endl;
                    }
                    cout << "la apuesta mas alta es de: " << mesa.GetHighestBet() << endl;
                }
                else if (event.mouseButton.button == sf::Mouse::Left && passButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    mesa.NextDealer();
                    counter++;
                }
                else if (event.mouseButton.button == sf::Mouse::Left && retireButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {

                }
                else if (event.mouseButton.button == sf::Mouse::Left && viewButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (view ==2) {
                        view = 1;
                    }
                    else {
                        view = 2;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Left && allButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    mesa.PlayerBet(mesa.m_players[mesa.m_dealerIndex].Bet(mesa.m_players[mesa.m_dealerIndex].GetChips()));
                    mesa.NextDealer();
                    counter++;
                    cout << "la apuesta mas alta es de: " << mesa.GetHighestBet() << endl;
                }
            }
        }

        playername = mesa.getnamedealer(mesa.GetDealer());
        textName.setString(playername);
        chips = "budget: " + to_string(mesa.m_players[mesa.m_dealerIndex].GetChips());
        textChips.setString(chips);

       




        if (counter == 4) { 
            for (auto& player : mesa.m_players) {
              if (player.NeedsToMatchBet(mesa.GetHighestBet())) {

                if (player.WantsToCall(mesa.GetHighestBet())) {
                    // El jugador decide igualar la apuesta
                    int difference = mesa.GetHighestBet() - player.GetCurrentBet();
                    player.Bet(difference);
                    mesa.PlayerBet(difference);
                }
                else {
                    player.Fold();
                }
              }
            }
            if (mesa.m_communityCards.size() < 5) {
                mesa.m_dealerIndex = 0;
                mesa.DealCommunityCard();
                counter = 0;
                mesa.ResetHighestBet();
            }
            else {
                mesa.EndGame();
              
              if (mesa.EnoughActivePlayers()) {
                  mesa.ActivateAllPlayers();
                  mesa.StartGame();
              }
              else {
                  mesa.m_dealerIndex = 0;
                  playername = mesa.getnamedealer(mesa.GetDealer());
                  cout << "ganaste " << playername;
              }
               
            }
        }







        window.clear();
        
        window.draw(tableSprite);
        // Dibuja los botones y el texto
        drawButton(window, addButton10, textAdd10);
        drawButton(window, addButton5, textAdd5);
        drawButton(window, passButton, textPass);
        drawButton(window, retireButton, textretire);
        drawButton(window, viewButton, textview);
        drawButton(window, viewName, textName);
        drawButton(window, viewChips, textChips);
        drawButton(window, allButton, textall);
        //dibuja las cartas en la mesa
        drawCard(window, mesa.getNamecommunity(0), sf::Vector2f(200, 150));
        drawCard(window, mesa.getNamecommunity(1), sf::Vector2f(300, 150));
        drawCard(window, mesa.getNamecommunity(2), sf::Vector2f(400, 150));
        drawCard(window, mesa.getNamecommunity(3), sf::Vector2f(500, 150));
        drawCard(window, mesa.getNamecommunity(4), sf::Vector2f(600, 150));

        drawCard(window, mesa.getNameCardPlayer(0, mesa.GetDealer(), view), sf::Vector2f(300, 450));
        drawCard(window,mesa.getNameCardPlayer(1,mesa.GetDealer(),view), sf::Vector2f(400,450));
        window.display();
    }

    return 0;
}