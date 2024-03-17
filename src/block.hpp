#pragma once
#include<vector>
#include<map>
#include"position.hpp"
#include"colors.hpp"
#include"BlockRotation.hpp"
class Block

{
public : 
	Block();
	void draw(sf::RenderTexture& texture , int offsetx, int offsety,bool Stop,sf::Clock& clock);
	void drawtra(sf::RenderTexture& texture, int offsetx, int offsety);

	void move(int rows, int cols);
	std::vector<Position> get_cell_postion();
	int id; 
	std::map < int, std::map<int,std::vector<Position>> > cells;
	void Rotate(int i );
	int getLastRow();
	void TranslateRotation();
	bool Pivot;
	void initialiserPivot();

	int rotationState;
	int pivot;
protected: 
	int cell_size;
	std::vector<sf::Color>	colors;  
	int rowOffset; 
	int colOffset; 
}; 
int min_col(std::vector<Position> curentCell);
int max_col(std::vector<Position> curentCell);
int min_row(std::vector<Position> currentCell);
