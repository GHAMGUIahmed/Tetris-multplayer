

#include"lobby.hpp"
int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tetris ");
    Lobby lobby;

    window.setFramerateLimit(120);
    sf::Color background = sf::Color(10, 10, 10);
    sf::Image icon;
    if (!icon.loadFromFile("icon.jpg")) std::cout << "no icon " << std::endl;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    bool focus = false;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::LostFocus) {
                focus = false;
            }
            if (event.type == sf::Event::GainedFocus) {
                focus = true;
            }
            if (event.type == sf::Event::TextEntered) {
                if (focus) {
                    if (event.text.unicode < 128)
                        lobby.text_input(static_cast<char>(event.text.unicode));
                }
            }
        }

        KeyboardManager::keyboardUpdate(focus);

        lobby.update();
        window.clear(background);
        lobby.draw(window);
        lobby.drawUserWorlds(window);
        window.display();

    }


    return 0;
}




