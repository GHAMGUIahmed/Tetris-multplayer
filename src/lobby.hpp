#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <ctype.h>

#include "server.hpp"
#include "client.hpp"
#include "tetris.hpp"
#include "clavier.hpp" 

class Lobby
{
    enum State {
        None,
        Join,
        Host,
        Singleplayer
    }; // le state de user dans la premiére fenêtre 

    enum Typing {
        Name,
        Address,
        Nothing
    }; // l'utilisateur est en train de faire quoi 

    State state;
    sf::Font lobbyFont;
    sf::Text lobbyText;
    sf::Texture texture; // pour le background 

    Server* server;
    Client* client;

    Tetris* game;

    bool gameStarted = false;
    Typing typing = Nothing;
    std::string typeText = "";
    std::string address = "127.0.0.1";

    std::string options[3] =
    {
    "Partie Solo",
    "Rejoindre une Partie ",
    "Hébérger une Partie"
    }; 

    int selected = 0;

public:
    static bool KEYBOARD_FOCUS;


    Lobby();
    void update();
    void draw(sf::RenderWindow& window);
    void text_input(char c);
    void drawUserWorlds(sf::RenderWindow& window);


};