#include "lobby.hpp"

Lobby::Lobby()
{
    state = None;
    lobbyFont.loadFromFile("assets/font.otf");
    lobbyText.setFont(lobbyFont);
    lobbyText.setCharacterSize(48);
    texture.loadFromFile("assets/window.jpg");
}

void Lobby::update()
{

    if (gameStarted) 
    {
        game->HandleInput();

        if (client != NULL) 
        {
            client->updatePieceState(&(game->currentBlock));
            client->updateState(&(game->grid));
            if (!client->isConnected())
                gameStarted = false;
            if (client->isGameFinished())
                gameStarted = false;
        }

        return;
    }
    





    if (state == None)
    {
        if (KeyboardManager::keyDown(sf::Keyboard::Key::Down))
        {
            selected++;
            if (selected > 2)selected = 2;
        }

        if (KeyboardManager::keyDown(sf::Keyboard::Key::Up))
        {
            selected--;
            if (selected < 0)selected = 0;
        }
       
        // detection de l'option choisi 
        if (KeyboardManager::keyDown(sf::Keyboard::Key::Enter) || KeyboardManager::keyDown(sf::Keyboard::Key::Space))
        {
            switch (selected) {
            case 0:
                state = Singleplayer;
                game = new Tetris(NULL);
                gameStarted = true;
                break;
            case 1:
                state = Join;
                typing = Address;
                typeText = "127.0.0.1";
                break;
            case 2:
                server = new Server();
                state = Host;
                typing = Name;
                break;
            }
        }
        return;
    }
    // ecrire le nom du client et l'adresse du host 
    if (typing != Nothing) 
    {

        if (KeyboardManager::keyDown(sf::Keyboard::Key::BackSpace)) {
            typeText = typeText.substr(0, typeText.length() - 1);
        }

        if (KeyboardManager::keyDown(sf::Keyboard::Key::Enter) && typeText.compare("") != 0) {
            if (typing == Address) {
                typing = Name;
                address = typeText;
                typeText = "";
            }
            else typing = Nothing;

            if (typing == Nothing)
                client = new Client(typeText, address);
        }
    }


    if (state == Host)
    {
        if (typing == Nothing) {
            if (server->isRunning() && KeyboardManager::keyDown(sf::Keyboard::Key::Enter)) {
                server->startGame();
                game = new Tetris(client);
                gameStarted = true;
            }
        }

        if (!server->isRunning()) {
            typing = Nothing;
        }

        if (KeyboardManager::keyDown(sf::Keyboard::Key::Escape)) {
            state = None;
            typeText = "";
            server->stop();
            delete server;
        }

    }

    if (state == Join && typing == Nothing) 
    {
        if (client->isGameStarted() && client->isConnected()) {
            game = new Tetris(client);
            gameStarted = true;
        }
        else if (!client->isConnected()) {
            if (KeyboardManager::keyDown(sf::Keyboard::Key::Escape)) {
                state = None;
                typeText = "";
            }
        }
    }
}
// pour lire la chaine  entré par le client 
void Lobby::text_input(char c) {
    if (!isalpha(c) && !isdigit(c) && !(c == ' ') && !(c == '.'))
        return;
    if (typing != Nothing) {
        typeText += c;
    }
}

void Lobby::draw(sf::RenderWindow& window)
{
    // background 
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.
    TextureSize = texture.getSize();//Get size of texture.
    sf::Vector2u renderSize = window.getSize();
    float ScaleX = (float)renderSize.x / TextureSize.x;
    float ScaleY = (float)renderSize.y / TextureSize.y;
    background.setTexture(texture);
    background.setScale(ScaleX, ScaleY);
    background.setColor(sf::Color(255, 255, 255, 150));
    window.draw(background);



    if (gameStarted)
    {
        game->draw();
        sf::Sprite spr = sf::Sprite(game->render.getTexture());
        window.draw(spr);
        return;

    }

    if (state == None)
    { 
        // dessiner les options 
        lobbyText.setCharacterSize(48);
        for (int i = 0; i < 3; i++) {
            lobbyText.setString(options[i]);
            lobbyText.setPosition(90 + (i == selected ? 45 : 0), 700 + 60 * i);
            window.draw(lobbyText);
        }
            return;
        }
    // pour guider l'utilisateur dans le mode multijoeur 


        if (typing != Nothing)
        {
            lobbyText.setCharacterSize(48);
            lobbyText.setPosition(100, 700);
            lobbyText.setFillColor(sf::Color::Red);
            if (typing == Name)
                lobbyText.setString("Entrer  le nom : ");
            else
                lobbyText.setString("Entrer l'adresse: ");
            window.draw(lobbyText);
            lobbyText.setFillColor(sf::Color::Yellow);
            lobbyText.setPosition(100, 750);
            lobbyText.setString(typeText + "");
            window.draw(lobbyText);
            lobbyText.setFillColor(sf::Color::Yellow);
        }

        if (state == Host) {

            lobbyText.setCharacterSize(48);
            lobbyText.setPosition(70, 620);
            lobbyText.setFillColor(sf::Color(255, 0, 0));

            if (server->isRunning()) {
                lobbyText.setString("Hébergement du server.");
                window.draw(lobbyText);
            }
            else {
                lobbyText.setString("échoue de rejoindre le serveur .");
                window.draw(lobbyText);

                lobbyText.setPosition(70, 820);
                lobbyText.setFillColor(sf::Color(255, 255, 0));
                lobbyText.setString("presser sur échap pour sortir ");
                window.draw(lobbyText);

                return;
            }

            lobbyText.setFillColor(sf::Color(255, 255, 255));
            lobbyText.setCharacterSize(48);
            lobbyText.setPosition(70, 850);
            lobbyText.setString("Joueurs:");
            window.draw(lobbyText);

            lobbyText.setFillColor(sf::Color(100, 100, 100));

            for (int i = 0; i < 4; i++) {
                lobbyText.setPosition(70, 900 + 50 * i);
                lobbyText.setString(server->getName(i));
                window.draw(lobbyText);
            }

            if (typing == Nothing) {
                lobbyText.setFillColor(sf::Color(0, 255, 0));
                lobbyText.setCharacterSize(48);
                lobbyText.setPosition(70, 1250);
                lobbyText.setString("Presser Enter pour le début ");
                window.draw(lobbyText);
            }

        }


        if (state == Join && typing == Nothing) {

            lobbyText.setCharacterSize(48);
            lobbyText.setPosition(70, 620);
            lobbyText.setFillColor(sf::Color::Red);

            if (client->isConnected()) {
                lobbyText.setString("En attente du Host .... ");
                window.draw(lobbyText);

                lobbyText.setFillColor(sf::Color(255, 255, 255));
                lobbyText.setCharacterSize(48);
                lobbyText.setPosition(70, 850);
                lobbyText.setString("Joueurs :");
                window.draw(lobbyText);

                lobbyText.setFillColor(sf::Color(100, 100, 100));

                int index = 0;
                for (int i = 0; i < 4; i++) {
                    if (client->getName(i).compare("") != 0) {
                        lobbyText.setPosition(70, 900 + 50 * index);
                        lobbyText.setString(client->getName(i));
                        window.draw(lobbyText);
                        index++;
                    }
                }
            }
            else {
                lobbyText.setString("échoue de connecter au serveur ");
                window.draw(lobbyText);

                lobbyText.setPosition(70, 820);
                lobbyText.setFillColor(sf::Color::Red);

                lobbyText.setString("Presser escape pour quitter");
                window.draw(lobbyText);
            }

        }

        if (client != NULL && client->isGameFinished()) {
            lobbyText.setFillColor(sf::Color::Red);
            lobbyText.setCharacterSize(48);
            lobbyText.setPosition(70, 1150);
            lobbyText.setString(client->getName(client->getGameWinner()) + "a gagné !");
            window.draw(lobbyText);
        }



    }

void Lobby::drawUserWorlds(sf::RenderWindow& window)
{
    if (client == NULL || !gameStarted) return;

    game->drawUserWorlds();
    sf::Sprite spr = sf::Sprite(game->render.getTexture());
    window.draw(spr);

}
