#pragma once 
#include<vector>
#include<SFML/Graphics.hpp>
#include"position.hpp"
class Grid
{ 
public : 
	Grid() ;
	int grid[22][10];
	void initialiser(); 
	void print(); 
	void draw(sf::RenderTexture& render,std::vector<Position> blockPlace);  
	bool IsCellOutside(int row, int col); 
	bool IsCellEmpty(int row, int col);
	int ClearFullRows();
	int LastRowGrid();
	int numRows;
	int numCols; 
	sf::Sprite sprite[22][10];



private: 
	
	int cell_size;
	std::vector<sf::Color> colors;
	/*std::vector<sf::Color> Get_Cell_Color();*/
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int number);
	std::vector<Position> WinyjemYt7at(std::vector<Position> tiles, int i);
}; 
int getLastRow(std::vector<Position> tiles);

