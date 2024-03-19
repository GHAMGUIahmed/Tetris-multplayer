
#ifndef CONNECTION_H
#define CONNECTION_H

#include "server.hpp"
#include <SFML/Network.hpp>

class Connection {

private:
    Server* server;    //Pointeur vers l'instance du serveur auquel la connexion est associ�e
    sf::TcpSocket* socket;    //Pointeur vers le socket TCP associ� � la connexion 
    std::string username;      //Username de la connexion     
    int id;             //ID de la connexion
    bool running;       //Indique si la connexion est en cours d'ex�cution
public:
    Connection(int id, Server* server, sf::TcpSocket* socket);
    void send(sf::Packet packet);  //Envoie un paquet via la connexion
    void run();         //Fonction de traitement principal de la connexion 
    void stop();        //Arr�t de la connexion
    std::string getName();      //Retourne le username de la connexion
};

#endif //CONNECTION_H