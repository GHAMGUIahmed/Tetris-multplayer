
#include <string>
#include <iostream>
#include <thread>
#include <SFML/Network.hpp>
#include"position.hpp"
#include "client.hpp"
#include "common.cpp"

using namespace sf;

void Client::connect() {

    connected = true;

    if (socket.connect(ip, 31621) != Socket::Done) {
        std::cout << "Client failed to connect to server" << std::endl;
        connected = false;
        return;
    }
    std::cout << "Sending username to server... " << std::endl;
    Packet userPacket;
    userPacket << username;
    if (socket.send(userPacket) != Socket::Done) {
        std::cout << "Failed to send username" << std::endl;
        connected = false;
        return;
    }


    Packet idPacket;
    if (socket.receive(idPacket) != Socket::Done) {
        std::cout << "Failed to get ID froms server" << std::endl;
        connected = false;
        return;
    }
    idPacket >> id;
    std::cout << "Client started with ID " << id << std::endl;

    while (connected) {

        Packet dPack;
        if (socket.receive(dPack) != sf::Socket::Done) {
            std::cout << "Server couldnt get pack from client " << std::endl;
            connected = false;
            return;
        }

        int type;
        dPack >> type;
        if (type == PACKET_TYPE_LOBBY) {
            for (int i = 0; i < 4; i++) {
                dPack >> users[i];
            }
        }
        else if (type == PACKET_TYPE_START) {
            gameStarted = true;
            gameFinished = false;
        }
        else if (type == PACKET_TYPE_WORLD) {

            int id = 0;
            int world[22][10];

            dPack >> id;

            for (int i = 0; i < 22; i++)  for (int j = 0; j < 10; j++) dPack >> world[i][j];
            /*for (int i = 0; i < 10 * 22; i++) {
                dPack >>world[i];
                //std::cout << world[i] << std::endl;
            }*/

            std::cout << "Client got world from " << id << std::endl;
            //userWorlds[id] = world;
            memcpy(userWorlds[id], world, sizeof(world));

        }
        else if (type == PACKET_TYPE_PIECE) {

            int id;
            //float x, y;

            dPack >> id;
            dPack >> pieceID[id];

            //userPiecePosition[id][0] = x;
            //userPiecePosition[id][1] = y;

            for (int i = 0; i < 4 * 4; i++)
                dPack >> userPiece[id][i];

        }
        else if (type == PACKET_TYPE_BLOCK) {

            addBlockCount++;
            dPack >> blockSender;

        }
        else if (type == PACKET_TYPE_GAMEOVER) {

            int id;
            dPack >> id;

            gameOver[id] = true;

        }
        else if (type == PACKET_TYPE_FINISHGAME) {

            int winner;
            dPack >> winner;

            resetState();

            gameStarted = false;
            gameFinished = true;
            gameWinner = winner;

        }
        else {
            std::cout << "Client got unknown pack type " << type;
        }

    }

}

void Client::send(Packet packet) {
    if (socket.send(packet) != Socket::Done) {
        std::cout << "Failed to send pack from client " << std::endl;
    }
}


Client::Client(std::string name, std::string address) {



    for (int i = 0; i < 4; i++)
        users[i] = "";

    resetState();

    ip = address;

    std::cout << "Starting client with name " << name << std::endl;

    for (int i = 0; i < 4; i++) {
        users[i] = "?";
    }

    username = name;



    std::thread th(&Client::connect, this);
    th.detach();
}

void Client::resetState() {
    std::cout << "Client reset state " << std::endl;
    // Reset users
    for (int i = 0; i < 4; i++) {
        gameOver[i] = false;

        for (int x = 0; x < 22; x++) for (int y = 0; y < 10; y++)
            userWorlds[i][x][y] = 0;
        for (int x = 0; x < 4 * 4; x++)
            userPiece[i][x] = 0;
    }
    addBlockCount = 0;
}

void Client::updateState(Grid* grid) {
    Packet packet;
    packet << (int)PACKET_TYPE_WORLD;
    packet << id;
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 10; j++) {
            packet << grid->grid[i][j];
            //if (grid->grid[j][i]) std::cout << grid->grid[j][i]<<std::endl;
        }

    }
    //grid->print();

    std::cout << "Client sending world" << std::endl;
    send(packet);
}

void Client::updatePieceState(Block* piece) {
    Packet packet;
    packet << (int)PACKET_TYPE_PIECE;
    packet << piece->id;

    std::vector<Position> tiles = piece->get_cell_postion();
    for (Position item : tiles) {
        packet << item.row << item.col;
    }
    std::cout << "Client sending piece" << std::endl;
    send(packet);
}

void Client::sendGameOver() {
    Packet packet;
    packet << (int)PACKET_TYPE_GAMEOVER;
    send(packet);
}

void Client::sendBlock() {
    Packet packet;
    packet << (int)PACKET_TYPE_BLOCK;
    send(packet);
}

bool Client::isConnected() {
    return connected;
}

int Client::getId() {
    return id;
}

std::string Client::getName(int i)
{

    return users[i];
}


bool Client::isGameStarted() {
    return gameStarted;
}

int** Client::getUserWorld(int usr) {
    //return userWorlds[usr];
    int** tempPtr = new int* [22]; // Alloue un tableau de pointeurs d'int

    // Copier les �l�ments du tableau 2D dans tempPtr
    for (int i = 0; i < 22; ++i) {
        // Allouer un tableau d'ints pour chaque ligne
        tempPtr[i] = new int[10];
        // Copier les �l�ments de userWorlds[usr][i] dans tempPtr[i]
        for (int j = 0; j < 10; ++j) {
            tempPtr[i][j] = userWorlds[usr][i][j];
        }
    }

    // Retourner tempPtr
    return tempPtr;
}

int Client::getPieceID(int usr) {
    return pieceID[usr];
}

int* Client::getPiece(int usr) {
    return userPiece[usr];
}
bool Client::getGameOver(int usr) {
    return gameOver[usr];
}

bool Client::addBlock() {
    if (addBlockCount > 0) {
        addBlockCount--;
        return true;
    }
    return false;
}


bool Client::isGameFinished() {
    return gameFinished;
}

int Client::getGameWinner() {
    return gameWinner;
}
