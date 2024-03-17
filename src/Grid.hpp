#pragma once 
#include<vector>
#include<SFML/Graphics.hpp>
#include"position.hpp" 

class Grid
{ 
public : 
	int grid[22][10];
	int numRows;
	int numCols;



	Grid();
	void initialiser(); 
	void print(); 
	void draw(sf::RenderTexture& render,std::vector<Position> blockPlace);  
	bool IsCellOutside(int row, int col); 
	bool IsCellEmpty(int row, int col);
	int ClearFullRows();



private: 
	
	int cell_size;
	std::vector<sf::Color> colors;
	/* ces trois fonctions pour la suppression des lignes */
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int number);

	/* l'argument i doit être getLastRow(tiles) 
	tiles c'est les positions courants  de block courant */
	std::vector<Position> PositionShadow(std::vector<Position> tiles, int i);

};


int getLastRow(std::vector<Position> tiles); /*Cette fonction sert à déterminer 
											la position de l'ombre du bloc dans la grille. */

