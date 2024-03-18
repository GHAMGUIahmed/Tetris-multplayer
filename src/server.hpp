
#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <SFML/Network.hpp>

class Server {
public:
    Server();
    void sendLobbyData();
    void sendAll(sf::Packet packet);
    void sendAllExcept(int id, sf::Packet packet);
    void run();
    void startGame();
    void setGameOver(int id);
    bool isRunning();
    void disconnect(int id);
    void stop();
    std::string getName(int player);
};

#endif //SERVER_H