#pragma once
#include<vector>

/* cette classe pour  modéliser une cellule en abscisse et ordonné */
class Position
{ 
public: 
	Position(int row, int col);
	int row; 
	int col; 
};
/*Cette fonction est employée dans la fonction Grid::PositionShadow afin de vérifier 
la translation d'un vecteur de position.
*/ 
 
std::vector<Position> translate(std::vector<Position> tiles, int x,int y );  
