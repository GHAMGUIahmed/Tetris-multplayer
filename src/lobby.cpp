#include "lobby.hpp"

Lobby::Lobby()
{
    state = None;
    lobbyFont.loadFromFile("assets/font.otf");
    lobbyText.setFont(lobbyFont);
    lobbyText.setCharacterSize(48);
    texture.loadFromFile("assets/tile.png");
}

void Lobby::update()
{
    if (gameStarted) {
        game->HandleInput();

        if (client != NULL) {
            client->updatePieceState(&(game->currentBlock));
            client->updateState(&(game->grid));
            if (!client->isConnected())
                gameStarted = false;
            if (client->isGameFinished())
                gameStarted = false;
        }

        return;
    }

    if (state == None) {
        if (KeyboardManager::keyDown(sf::Keyboard::Key::Down)) {
            selected++;
            if (selected > 2)selected = 2;
        }

        if (KeyboardManager::keyDown(sf::Keyboard::Key::Up)) {
            selected--;
            if (selected < 0)selected = 0;
        }

        if (KeyboardManager::keyDown(sf::Keyboard::Key::Enter) || KeyboardManager::keyDown(sf::Keyboard::Key::Space)) {
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

    if (typing != Nothing) {

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


    if (state == Host) {
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

    if (state == Join && typing == Nothing) {
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

void Lobby::text_input(char c) {
    if (!isalpha(c) && !isdigit(c) && !(c == ' ') && !(c == '.'))
        return;
    if (typing != Nothing) {
        typeText += c;
    }
}

void Lobby::draw(sf::RenderWindow& window)
{
    if (gameStarted)
    {
        game->draw();
        sf::Sprite spr = sf::Sprite(game->render.getTexture());
        window.draw(spr);
        return;

    }
    /* lobbyText.setFillColor(sf::Color(255, 255, 255));
     lobbyText.setCharacterSize(64);
     lobbyText.setString("C++tris");
     lobbyText.setPosition(70, 550);
     window.draw(lobbyText);
     if (typing != Nothing)*/
    if (state == None)
    {
        lobbyText.setCharacterSize(48);
        for (int i = 0; i < 3; i++) {
            lobbyText.setString(options[i]);
            lobbyText.setPosition(90 + (i == selected ? 45 : 0), 700 + 60 * i);
            window.draw(lobbyText);
        }
        return;
    }

    if (typing != Nothing)
    {
        lobbyText.setCharacterSize(48);
        lobbyText.setPosition(100, 700);
        lobbyText.setFillColor(sf::Color(100, 100, 100));
        if (typing == Name)
            lobbyText.setString("Enter name: ");
        else
            lobbyText.setString("Enter address: ");
        window.draw(lobbyText);
        lobbyText.setFillColor(sf::Color(255, 255, 0));
        lobbyText.setPosition(100, 750);
        lobbyText.setString(typeText + "");
        window.draw(lobbyText);
        lobbyText.setFillColor(sf::Color(255, 255, 255));
    }

    if (state == Host) {
        lobbyText.setCharacterSize(48);
        lobbyText.setPosition(70, 620);
        lobbyText.setFillColor(sf::Color(255, 0, 0));

        if (server->isRunning()) {
            lobbyText.setString("Hosting server.");
            window.draw(lobbyText);
        }
        else {
            lobbyText.setString("Failed to start server.");
            window.draw(lobbyText);

            lobbyText.setPosition(70, 820);
            lobbyText.setFillColor(sf::Color(255, 255, 0));
            lobbyText.setString("Press escape to exit");
            window.draw(lobbyText);

            return;
        }

        lobbyText.setFillColor(sf::Color(255, 255, 255));
        lobbyText.setCharacterSize(48);
        lobbyText.setPosition(70, 850);
        lobbyText.setString("Players:");
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
            lobbyText.setString("Press Enter to start");
            window.draw(lobbyText);
        }

    }

    if (state == Join && typing == Nothing) {

        lobbyText.setCharacterSize(48);
        lobbyText.setPosition(70, 620);
        lobbyText.setFillColor(sf::Color(255, 0, 0));

        if (client->isConnected()) {
            lobbyText.setString("Waiting for host...");
            window.draw(lobbyText);

            lobbyText.setFillColor(sf::Color(255, 255, 255));
            lobbyText.setCharacterSize(48);
            lobbyText.setPosition(70, 850);
            lobbyText.setString("Players:");
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
            lobbyText.setString("Failed to connect");
            window.draw(lobbyText);

            lobbyText.setPosition(70, 820);
            lobbyText.setFillColor(sf::Color(255, 255, 0));

            lobbyText.setString("Press escape to exit");
            window.draw(lobbyText);
        }

    }

    if (client != NULL && client->isGameFinished()) {
        lobbyText.setFillColor(sf::Color(0, 255, 255));
        lobbyText.setCharacterSize(48);
        lobbyText.setPosition(70, 1150);
        lobbyText.setString(client->getName(client->getGameWinner()) + " won the round!");
        window.draw(lobbyText);
    }



}
void Lobby::drawUserWorlds(sf::RenderWindow& window)
{
    if (client == NULL || !gameStarted) return;

    game->drawUserWorlds();
    sf::Sprite spr = sf::Sprite(game->render.getTexture());
    window.draw(spr);













   /*int cell_size = 35;
    int mini_cell_size = 20;
    int border = 15;
    int starty = 52;
    int startx = cell_size * 10 + 100;
    std::vector<sf::Color> colors = GetCellColors();
    

    int step = 0;
    int usr = -1;

    for (int n = 0; n < 2; n++) {

        int posy = step * mini_cell_size * 22 + step * 66;

        usr++;
        if (client->getId() == usr) {
            usr++;
        }



        step++;
        int** world = client->getUserWorld(usr);

        int k = 0;

        world[0][0] = 0;
        for (int i = 0; i < 22; ++i) {
            int temp = world[i][0];
            for (int j = 0; j < 9; ++j) {
                world[i][j] = world[i][j + 1];
            }
            world[i][9] = temp;
        }
        game->drawText(client->getName(usr), 40, 500, posy,false);
        for (int x = 0; x < 22; x++) {
            for (int y = 0; y < 10; y++) {
                sf::RectangleShape rectangle1;
                int cell_value = world[x][y];

                sf::RectangleShape rectangle;
                rectangle1.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
                rectangle1.setPosition(y * mini_cell_size + 1000, posy + x * mini_cell_size + 50);
                rectangle1.setOutlineThickness(1);
                rectangle1.setOutlineColor(sf::Color::Cyan);

                rectangle1.setFillColor(colors[cell_value]);

                window.draw(rectangle1);
            }


        }
        
        game->drawText(client->getName(usr), 40, 500, posy, false);
        sf::Sprite spr = sf::Sprite(game->render.getTexture());
        window.draw(spr);
        

        int pieceID = client->getPieceID(usr);
        int* piece = client->getPiece(usr);

        for (int p = 0; p < 8; p += 2) {

            /*block.setColor(PIECE_COLOR[piece[p] - 1]);
            block.setPosition(posx + (p % 4 + piece_x) * tile, posy + (p / 4 + piece_y) * tile);
            window.draw(block);*/
    /*
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
            rectangle.setPosition(piece[p + 1] * mini_cell_size + 1000, posy + piece[p] * mini_cell_size + 50);
            // colors[pieceID].a = 255;

            rectangle.setFillColor(colors[pieceID]);

            window.draw(rectangle);
        }

    }/*
    usr++;
    int** world = client->getUserWorld(usr);
    int posy = 300;
    int posx = 1000 + 22 * mini_cell_size;
    int k = 0;

    world[0][0] = 0;
    for (int i = 0; i < 22; ++i) {
        int temp = world[i][0];
        for (int j = 0; j < 9; ++j) {
            world[i][j] = world[i][j + 1];
        }
        world[i][9] = temp;
    }
    game->drawText(client->getName(usr), 40, posx, posy,false);
    for (int x = 0; x < 22; x++) {
        for (int y = 0; y < 10; y++) {
            sf::RectangleShape rectangle1;
            int cell_value = world[x][y];

            sf::RectangleShape rectangle;
            rectangle1.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
            rectangle1.setPosition(y * mini_cell_size + posx, posy + x * mini_cell_size + 11);
            rectangle1.setOutlineThickness(1);
            rectangle1.setOutlineColor(sf::Color::Cyan);

            rectangle1.setFillColor(colors[cell_value]);

            window.draw(rectangle1);
        }


    }/*

    int pieceID = client->getPieceID(usr);
    int* piece = client->getPiece(usr);

    for (int p = 0; p < 8; p += 2) {

        /*block.setColor(PIECE_COLOR[piece[p] - 1]);
        block.setPosition(posx + (p % 4 + piece_x) * tile, posy + (p / 4 + piece_y) * tile);
        window.draw(block);*/
/*
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
        rectangle.setPosition(piece[p + 1] * mini_cell_size + posx, posy + piece[p] * mini_cell_size + 11);
        // colors[pieceID].a = 255;

        rectangle.setFillColor(colors[pieceID]);

        window.draw(rectangle);
    }*/

}
