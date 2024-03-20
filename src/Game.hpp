#pragma once 
#include"Grid.hpp"
#include"blocks.hpp"
#include<SFML/Audio.hpp> 
class Game
{

	
protected:
	std::vector<Block> blocks;
	
	bool Animated; // utilisé pour savoir si le current block est en train de verrouiller
	//on anime son verrou  
	int BlockGiven; // utile pour définir le niveau
	bool gameOver;
	int score;
	int level;
	// pour les animation de notre Game 
	sf::Music musicGame;
	sf::Sound soundRotate;
	sf::Sound soundClear;
	sf::SoundBuffer buffer; // les fichiers de sound 
	sf::SoundBuffer buffer1;
	sf::SoundBuffer DropBuffer; 
	sf::Sound Drop;

	sf::Clock ClockFit; // un temp avant de verrouiller le block
	sf::Clock ClockChute; // aprés un certain temp le block descend 
	sf::Font font;
	sf::Clock clockAnimated; // un temps pour l'animation



	Game();
	std::vector<Block> GetAllBlocks();
	Block GetRandomBlock(); 
	// les mouvements du block 

	void MoveBlockleft();
	void MoveBlockRight();
	void MoveBlockDown();
	void InstantDrop();
	void RotateBlock(int i);
	// passer d'un block à un autre block 
	void LockBlock();
	bool BlockFits(); 
	bool IsBlookOutside();
	
	void Reset();
	void chutelibre(); // pour faire descendre le block automatiquement 
	int GetClockChuteMicro();
	void UpdateLevel();
	void UpdateScore(int linesCleared, int moveDownPoints);
public:

	void HandleInput(); // entrée du clavier 
	Block currentBlock;
	Block nextBlock;
	Grid grid;




};