
#pragma once 

#include <SFML/Window.hpp>
 
/*
Ce fichier a pour objectif de personnaliser l
utilisation du clavier en fonction de nos besoins spécifiques. 
4Nous cherchons à différencier entre le moment où un bouton est enfoncé (pressed) 
et celui où il est maintenu enfoncé (down), car la gestion par défaut dans SFML est jugée trop rapide.*/

namespace KeyboardManager {
    enum State {
        None,
        Down,
        Pressed
    };
    void keyboardUpdate(bool focus);
    bool keyDown(sf::Keyboard::Key key);
    bool keyPressed(sf::Keyboard::Key key);
};