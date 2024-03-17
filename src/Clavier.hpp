
#pragma once 

#include <SFML/Window.hpp>

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