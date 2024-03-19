#include <iostream>
#include <thread>
#include <SFML/Network.hpp>

#include "connection.hpp"
#include "common.cpp"

using namespace sf;
using namespace std;

Connection::Connection(int id, Server* server, TcpSocket* socket) {

    cout << "Starting client connection " << endl;
    //Initialisation des attributs pass�s en arguments
    this->id = id;
    this->server = server;
    this->socket = socket;
    running = true;
    //lancement d'un nouveau thread pour la m�thode Connection::run d�tach� du thread principal
    thread th(&Connection::run, this);
    th.detach();

}

void Connection::send(Packet packet) {
    if (socket->send(packet) != sf::Socket::Done) {
        cout << "Server failed to send packet to connection " << id << endl;
        running = false;
        server->disconnect(id);
    }
}

void Connection::stop() {
    running = false;
    socket->disconnect();
}

void Connection::run() {
    cout << "Getting client name... " << endl;

    Packet namePacket;
    //r�ception du username de la connexion et d�connexion en cas d'�chec
    if (socket->receive(namePacket) != sf::Socket::Done) {
        cout << "Server couldnt get username from client " << endl;
        running = false;
        server->disconnect(id);
        return;
    }

    namePacket >> username;
    cout << "Server got name: " << username << endl;
    Packet idPacket;
    idPacket << id;
    send(idPacket);
    server->sendLobbyData();
    while (running) {       //tant que la connexion s'ex�cute on re�oit les packets et on les traite type par type
        Packet packet;
        if (socket->receive(packet) != Socket::Done) {
            cout << "Failed to receive pack from client " << endl;
            running = false;
            server->disconnect(id);
            break;
        }

        int type;
        packet >> type;

        if (type == PACKET_TYPE_WORLD) {    //R�ception et transmission d'une grille sauf l'exp�diteur

            int world[10 * 22];

            for (int i = 0; i < 10 * 22; i++) {
                packet >> world[i];
            }

            Packet wPack;

            wPack << (int)PACKET_TYPE_WORLD;
            wPack << id;

            for (int i = 0; i < 22 * 10; i++)
                wPack << world[i];

            server->sendAllExcept(id, wPack);

        }
        else if (type == PACKET_TYPE_PIECE) {    //R�ception et transmission d'une pi�ce sauf � l'exp�diteur


            int pieceID;
            packet >> pieceID;
            int piece[4 * 2];
            for (int i = 0; i < 4 * 2; i++) {
                packet >> piece[i];
            }

            Packet pPack;
            pPack << (int)PACKET_TYPE_PIECE;
            pPack << id << pieceID;

            for (int i = 0; i < 4 * 2; i++)
                pPack << piece[i];

            server->sendAllExcept(id, pPack);

        }
        else if (type == PACKET_TYPE_GAMEOVER) {    //R�ception et transmission du signal de perte sauf l'exp�diteur
            Packet goPack;
            goPack << (int)PACKET_TYPE_GAMEOVER;
            goPack << id;
            server->sendAllExcept(id, goPack);
            server->setGameOver(id);
        }

    }

}

std::string Connection::getName()
{
    return username;
}