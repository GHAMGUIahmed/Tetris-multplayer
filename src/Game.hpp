#pragma once 
#include"Grid.hpp"
#include"blocks.hpp"
#include<SFML/Audio.hpp> 
class Game
{

	public: 
	Grid grid; 

	std::vector<Block> blocks;
	Block currentBlock; 
	Block nextBlock;

	bool Animated; 
	int BlockGiven; 
	bool gameOver;
	int score;
	int level;
	// pour les animation de notre Game 
	sf::Music musicGame;
	sf::Sound soundRotate;
	sf::Sound soundClear;
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer1;
	sf::SoundBuffer DropBuffer;
	sf::Sound Drop;
	sf::Clock ClockFit;
	sf::Clock ClockChute;
	sf::Font font;
	sf::Clock clockAnimated;

	//sf::RenderTexture render;



	Game();
	std::vector<Block> GetAllBlocks();
	Block GetRandomBlock();
	void MoveBlockleft();
	void MoveBlockRight();
	void MoveBlockDown();
	void InstantDrop();
	void RotateBlock(int i);
	void LockBlock();
	bool BlockFits();
	void Reset();
	bool IsBlookOutside();
	void chutelibre();
	int GetClockChuteMicro();

	void UpdateLevel();
	void UpdateScore(int linesCleared, int moveDownPoints);
public:

	void HandleInput();




};