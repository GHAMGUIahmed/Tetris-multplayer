
#pragma once 

#include <string>
#include <SFML/Network.hpp>

class Server {
public:
    Server();
    void sendLobbyData();        //Envoi des usernames à tous les clients
    void sendAll(sf::Packet packet);        //Envoi d'un paquet à tous les clients
    void sendAllExcept(int id, sf::Packet packet);        //Envoi d'un paquet à tous les clients sauf celui spécifié en argument
    void run();        //Fonction principale pour l'exécution du serveur
    void startGame();        //Démarre le jeu pour tous les clients connectés
    void setGameOver(int id);        //Définition de l'état de perte pour le joueur spécifié
    bool isRunning();            //Indique si le serveur est en exécution 
    void disconnect(int id);        //Déconnexion du client spécifié
    void stop();        //Arrêt de l'exécution
    std::string getName(int player);        //Retourne le username du joueur spécifié
};

