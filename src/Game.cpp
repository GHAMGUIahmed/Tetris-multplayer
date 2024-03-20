#include"Game.hpp"
#include<random> 
#include<iostream>
#include<time.h>
#include"Clavier.hpp"
Game::Game()
{
	grid = Grid();
	BlockGiven = 0;

	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	UpdateLevel();
	Animated = false;
	gameOver = false;
	if (!musicGame.openFromFile("assets/music.ogg"))
	{
		std::cout << "error" << std::endl;
	}

	if (!font.loadFromFile("assets/Arial.ttf")) std::cout << "error to load ff file " << std::endl;

	musicGame.setVolume(50);
	musicGame.play();
	musicGame.setLoop(true);
	if (!buffer.loadFromFile("assets/rotate.ogg")) {
		std::cout << "mnjmch nhell t3 rotate" << std::endl;
	}
	soundRotate.setBuffer(buffer);
	soundRotate.setVolume(200);
	//sf::SoundBuffer buffer1;
	if (!buffer1.loadFromFile("assets/clear.ogg")) { std::cout << "mnjmch nhell t3 clear" << std::endl; }
	soundClear.setBuffer(buffer1);
	soundClear.setVolume(500);
	if (!DropBuffer.loadFromFile("assets/drop.ogg")) { std::cout << "njmch nhell drop " << std::endl; }
	Drop.setBuffer(DropBuffer);

	Drop.setVolume(20);
}
std::vector<Block> Game::GetAllBlocks()
{

	return { OBlock(),TBlock(),IBlock(),SBlock(),ZBlock(), LBlock(),JBlock() };

}

Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetAllBlocks();
	}
	// pour avoir le même block si tous les blocks ont été donnés 
	int radomIndex = rand() % blocks.size();
	Block block = blocks[radomIndex];
	blocks.erase(blocks.begin() + radomIndex);
	UpdateLevel();
	BlockGiven++;
	return block;
}

void Game::MoveBlockleft()
{
	if (!gameOver)
	{
		currentBlock.move(0, -1);
		if (IsBlookOutside() || !BlockFits()) MoveBlockRight();
	}
}

void Game::MoveBlockRight()
{
	if (!gameOver) {
		currentBlock.move(0, 1);
		if (IsBlookOutside() || !BlockFits()) currentBlock.move(0, -1);
	}
}
void Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.move(1, 0);
		if (IsBlookOutside() || !BlockFits())
		{
			currentBlock.move(-1, 0);
			Animated = true;
			if (ClockFit.getElapsedTime().asMilliseconds() > 1000)
			{
				LockBlock();
				Animated = false;
			}
		}
		else { ClockFit.restart(); }

	}
}

void Game::InstantDrop()
{
	if (!gameOver) {
		while (true)
		{
			currentBlock.move(1, 0);
			if (IsBlookOutside() || !BlockFits()) {

				currentBlock.move(-1, 0);
				LockBlock();
				Animated = false;
				break;
			}
		}
		Drop.play();
	}
}

void Game::chutelibre()
{

	if (ClockChute.getElapsedTime().asMilliseconds() > GetClockChuteMicro())
	{


		MoveBlockDown();
		ClockChute.restart();
	}
}


bool Game::IsBlookOutside()
{
	std::vector<Position> tiles = currentBlock.get_cell_postion();
	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.col)) return true;
	}
	return false;
}
void Game::RotateBlock(int i)
{
	if (!gameOver)
	{
		currentBlock.Rotate(i);
		if (IsBlookOutside() || !BlockFits())
		{
			currentBlock.Rotate(-1);
		}
		soundRotate.play();
	}
}


void Game::LockBlock() // pour figer le bloque 
{

	std::vector<Position> tiles = currentBlock.get_cell_postion();

	for (Position item : tiles)
	{
		grid.grid[item.row][item.col] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (!BlockFits())
	{
		gameOver = true;
	}
	nextBlock = GetRandomBlock();

	int rowsCleared = grid.ClearFullRows();

	if (rowsCleared > 0)
	{
		soundClear.play();

	}
	UpdateLevel();
	UpdateScore(rowsCleared, 0);
}


bool Game::BlockFits() 
{
	std::vector<Position> tiles = currentBlock.get_cell_postion();
	for (Position item : tiles)
	{
		if (!grid.IsCellEmpty(item.row, item.col))
			return false;
	}
	return true;

}





void Game::UpdateLevel()
{
	level = BlockGiven / 10 + 1;
}

void Game::UpdateScore(int LinesCleared, int moveDownPoints)
{
	switch (LinesCleared)
	{
	case 1:
		score += 40 * (level + 1);
		break;
	case 2:
		score += 100 * (level + 1);
		break;
	case 3:
		score += 300 * (level + 1);
		break;
	case 4:
		score += 1200 * (level + 1);
	default:
		break;

	}
}

void Game::HandleInput()
{
	chutelibre();
	if (gameOver && KeyboardManager::keyDown(sf::Keyboard::Enter))
	{
		gameOver = false;
		Reset();
	}
	if (KeyboardManager::keyDown(sf::Keyboard::Left))
	{
		MoveBlockleft();

	}
	if (KeyboardManager::keyDown((sf::Keyboard::Right)))
	{
		MoveBlockRight();
	}
	if (KeyboardManager::keyDown((sf::Keyboard::Down)))
	{
		MoveBlockDown();
	}
	if (KeyboardManager::keyDown((sf::Keyboard::Space)))
	{
		InstantDrop();

	}
	if (KeyboardManager::keyDown((sf::Keyboard::Z)))
	{
		RotateBlock(1);
	}

	if (KeyboardManager::keyDown((sf::Keyboard::W)))
	{
		RotateBlock(-1);
	}
}

void Game::Reset()
{
	grid.initialiser();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
	level = 1;
	BlockGiven = 0;
}
int  Game::GetClockChuteMicro()
{
	switch (level)
	{
	case 1: return 1000;
	case 2: return 800;
	case 3: return 600;
	case 4: return 500;
	case 5: return 300;
	case 6: return 250;
	case 7: return 100;
	case 8: return 50;
	default:
		return 0;
	}
}





