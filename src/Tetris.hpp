#pragma once 
#include "Game.hpp"
#include"server.hpp"
#include"client.hpp"
#include<cmath> 
class Tetris:public Game
{
public:
	sf::RenderTexture render;
	Client* client;
	bool gameStarted = false;
	Tetris(Client* cli) :client(cli), gameStarted(false)
	{
		render.create(3000, 2000);

	}
	void drawText(sf::String content, int size, float x, float  y,bool Gras);
	void drawRectangle(float length, float width, float x, float y);
	void drawUserWorlds();
	void draw();

};