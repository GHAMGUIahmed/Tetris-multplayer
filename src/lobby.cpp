#include "lobby.hpp"

Lobby::Lobby()
{
    state = None;        // Initialise l'état du lobby à None
    lobbyFont.loadFromFile("assets/font.otf");       // Charge la police de caractères depuis un fichier 
    lobbyText.setFont(lobbyFont);        // Applique la police de caractères au texte du lobby
    lobbyText.setCharacterSize(48);        // Définit la taille des caractères du texte du lobby
    texture.loadFromFile("assets/tile.png");        // Charge la texture utilisée dans le lobby depuis un fichier
}

void Lobby::update()
{
    if (gameStarted) {            

        //Si le jeu a commencé on traite l'entrée au clavier du joueur
        game->HandleInput();
        //Si on est en mode multijoueur on met à jour l'état de la grille et de la pièce en mouvement au serveur
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
    //Si on est dans aucun mode, on traite l'entrée du clavier de façon à sélectionner une option 
    if (state == None) {
        if (KeyboardManager::keyDown(sf::Keyboard::Key::Down)) {
            selected++;
            if (selected > 2)selected = 2;
        }

        if (KeyboardManager::keyDown(sf::Keyboard::Key::Up)) {
            selected--;
            if (selected < 0)selected = 0;
        }
        //Une fois l'utilisateur sélectionne l'option, on met l'état du lobby et l'état de la saisie selon le choix
        if (KeyboardManager::keyDown(sf::Keyboard::Key::Enter) || KeyboardManager::keyDown(sf::Keyboard::Key::Space)) {
            switch (selected) {
            case 0:
                state = Singleplayer;
                game = new Tetris(NULL);
                gameStarted = true;
                break;
            case 1:
                state = Join;
                typing = Address;  //Si le joueur veut rejoindre un jeu, il doit taper tout d'abord l'adresse IP du serveur
                typeText = "127.0.0.1";
                break;
            case 2:
                server = new Server();
                state = Host;
                typing = Name;        //Si le joueur veut héberger, on initialise le serveur sur son appareil et il doit juste taper son username
                break;
            }
        }
        return;
    }

    if (typing != Nothing) {
        //On gère l'entrée au clavier
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
            //Si l'hébergeur a tapé son nom et a appuié entrée, on démarre le jeu 
            if (server->isRunning() && KeyboardManager::keyDown(sf::Keyboard::Key::Enter)) {
                server->startGame();
                game = new Tetris(client);
                gameStarted = true;
            }
        }
        
        if (!server->isRunning()) {
            typing = Nothing;
        }
        //Si on tape échap on arrête le serveur
        if (KeyboardManager::keyDown(sf::Keyboard::Key::Escape)) {
            state = None;
            typeText = "";
            server->stop();
            delete server;
        }

    }

    if (state == Join && typing == Nothing) {
        //Si le joueur voulant rejoindre un jeu s'est connecté, on crée l'instance du jeu Tetris et il attend que l'hébergeur démarre
        if (client->isGameStarted() && client->isConnected()) {
            game = new Tetris(client);
            gameStarted = true;
        }
        //S'il n'est pas connecté on gère l'erreur
        else if (!client->isConnected()) {
            if (KeyboardManager::keyDown(sf::Keyboard::Key::Escape)) {
                state = None;
                typeText = "";
            }
        }
    }
}

void Lobby::text_input(char c) {
    //On vérifie si le caractère n'est ni une lettre, ni un chiffre, ni un espace, ni un point
    if (!isalpha(c) && !isdigit(c) && !(c == ' ') && !(c == '.'))
        return;   // Si ce n'est pas le cas, on retourne sans effectuer aucune action
    //On vérifie s'il y a une saisie en cours
    if (typing != Nothing) {
        typeText += c; //On ajoute le caractère à la chaîne de texte en cours de saisie
    }
}

void Lobby::draw(sf::RenderWindow& window)
{    
    //Si le jeu a commencé, on affiche la grille, le score et le level de l'utilisateur
    if (gameStarted)
    {
        game->draw();
        sf::Sprite spr = sf::Sprite(game->render.getTexture());
        window.draw(spr);
        return;

    }
    //S'il n'y a aucune option choisie, on affiche les options à choisir
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
    //Si l'état de saisie est actif, on affiche ce qu'on demande d'écrire et ce que l'utilisateur écrit
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
    //On gère l'affichage lors de l'attenet de la connexion des joueurs
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
    //On gère l'affichage lorsque l'utilisateur attende que l'hébergeur démarre le jeu
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
    //Si le jeu a commencé et on est en mode multijoueur, on affiche les grilles des joueurs adverses
    if (client == NULL || !gameStarted) return;

    game->drawUserWorlds();
    sf::Sprite spr = sf::Sprite(game->render.getTexture());
    window.draw(spr);

}
