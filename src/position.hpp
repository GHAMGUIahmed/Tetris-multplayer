#pragma once
#include<vector>

/* cette classe pour  mod�liser une cellule en abscisse et ordonn� */
class Position
{ 
public: 
	Position(int row, int col);
	int row; 
	int col; 
};
/*Cette fonction est employ�e dans la fonction Grid::PositionShadow afin de v�rifier 
la translation d'un vecteur de position.
*/ 
 
std::vector<Position> translate(std::vector<Position> tiles, int x,int y );  
