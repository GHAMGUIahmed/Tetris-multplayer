
#pragma once 

#include <SFML/Window.hpp>
 
/*
Ce fichier a pour objectif de personnaliser l
utilisation du clavier en fonction de nos besoins sp�cifiques. 
4Nous cherchons � diff�rencier entre le moment o� un bouton est enfonc� (pressed) 
et celui o� il est maintenu enfonc� (down), car la gestion par d�faut dans SFML est jug�e trop rapide.*/

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