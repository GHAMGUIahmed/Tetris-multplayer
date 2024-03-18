
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <SFML/Network.hpp>
#include "block.hpp"
#include"Grid.hpp"
class Client {

private:

    sf::TcpSocket socket;
    bool connected = false;

    std::string* users = new std::string[4];

<<<<<<< HEAD
    std::string username;
    std::string ip;


    int id;
=======
    std::string username;    //Nom d'utilisateur du client
    std::string ip;          //Adresse IP du serveur


    int id;                 //ID du client


    int userWorlds[4][22][10];    //Les grilles de tous les joueurs

    
    int** userPiece;      //Les positions des cellules des pièces en mouvement
    int pieceID[4];               //Les IDs des pièces en mouvement 


    int userWorlds[4][22][10];
    //std::map<int, std::vector<int>> userWorlds;

    int addBlockCount = 0;
    int blockSender = 0;

    float userPiecePosition[4][2];
    int userPiece[4][4 * 4];
    int pieceID[4];

    bool gameOver[4];

    bool gameStarted = false;
    bool gameFinished = false;
    int gameWinner = 0;

    void connect();
    void send(sf::Packet packet);

public:
    Client(std::string name, std::string address);
    void resetState();
    void updateState(Grid* grid);
    void updatePieceState(Block* piece);
    void sendGameOver();
    void sendBlock();
    bool isConnected();
    std::string getName(int i);
    bool isGameStarted();
    int** getUserWorld(int usr);
    int getPieceID(int usr);
    int* getPiece(int usr);
    bool getGameOver(int usr);
    bool isGameFinished();
    int getGameWinner();
    bool addBlock();
    //std::string getBlockSender();
    int getId();


};

#endif //CLIENT_H
