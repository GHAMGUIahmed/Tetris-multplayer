#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <SFML/Network.hpp>
#include "block.hpp"
#include"Grid.hpp"
class Client {

private:

    sf::TcpSocket socket;      //Socket TCP pour communiquer avec le serveur
    bool connected = false;    //Indicateur de l'état de connexion du client

    std::string* users = new std::string[4];   //Les noms d'utilisateurs

    std::string username;    //Nom d'utilisateur du client
    std::string ip;          //Adresse IP du serveur


    int id;                 //ID du client


    int userWorlds[4][22][10];    //Les grilles de tous les joueurs

    
    int** userPiece;      //Les positions des cellules des pièces en mouvement
    int pieceID[4];               //Les IDs des pièces en mouvement 

    bool gameOver[4];             //Les états des jeux de chaque joueurs

    bool gameStarted = false;     //Indique si le jeu a commencé
    bool gameFinished = false;    //Indique si le jeu est terminé
    int gameWinner = 0;           //ID du gagnant

    void connect();               //établir la connexion avec le serveur
    void send(sf::Packet packet);    //envoie un packet au serveur

public:
    Client(std::string name, std::string address);
    void resetState();    //réinitialise le jeu du client
    void updateState(Grid* grid);    //envoie l'état actuel de la grille 
    void updatePieceState(Block* piece);    //envoie les positions des cellules de la pièce en mouvement
    void sendGameOver();        //envoie un signal quand le client perd
    bool isConnected();         //renvoie si le joueur est connecté
    std::string getName(int i);     //renvoie le username du joueur dont l'ID est passé en argument
    bool isGameStarted();           //renvoie si le jeu a commencé
    int** getUserWorld(int usr);        //renvoie la grille du joueur dont l'ID est passé en argument
    int getPieceID(int usr);            //renvoie l'ID de la pièce en mouvement du joueur dont l'ID est passé en argument
    int* getPiece(int usr);             //renvoie les positions des cellules de la pièce en mouvement du joueur dont l'ID est passé en argument
    bool getGameOver(int usr);          //renvoie l'état du jeu du joueur dont l'ID est passé en argument
    bool isGameFinished();              //renvoie si le jeu est terminé
    int getGameWinner();        //renvoie l'ID du gagnant
    int getId();                //renvoie l'ID du client


};
#endif CLIENT_H

