
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

    std::string username;
    std::string ip;

    
    int id;

    
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
