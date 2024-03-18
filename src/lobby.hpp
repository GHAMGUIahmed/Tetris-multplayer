#pragma once 
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
    };

    enum Typing {
        Name,
        Address,
        Nothing
    };

    State state;        //État actuel du lobby
    sf::Font lobbyFont;        // Police de caractères pour le lobby
    sf::Text lobbyText;        // Texte utilisé dans le lobby
    sf::Texture texture;       // Texture utilisée dans le lobby 

    Server* server;            // Pointeur vers l'instance du serveur 
    Client* client;            // Pointeur vers l'instance du client

    Tetris* game;               // Pointeur vers l'instance du jeu Tetris

    bool gameStarted = false;        //Indique si le jeu a commencé
    Typing typing = Nothing;         // État de la saisie
    std::string typeText = "";       //Texte en cours de saisie
    std::string address = "127.0.0.1";        //Adresse IP par défaut (localhost)

    std::string options[3] =           //Options du jeu 
    {
    "Singleplayer",
    "Join game",
    "Host game"
    };

    int selected = 0;            //Indice de l'option sélectionnée

public:
    static bool KEYBOARD_FOCUS;        //Indique si le focus clavier est sur la fenêtre du lobby


    Lobby();
    void update();        //Met à jour l'état du lobby
    void draw(sf::RenderWindow& window);        //Dessine le contenu du lobby sur la fenêtre
    void text_input(char c);            //Gère la saisie de texte dans le lobby
    void drawUserWorlds(sf::RenderWindow& window);    //Dessine les grilles des joueurs adverses sur la fenêtre


};
