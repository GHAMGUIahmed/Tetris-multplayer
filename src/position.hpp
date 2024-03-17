#pragma once
#include<vector>
class Position
{ 
public: 
	Position(int row, int col);
	int row; 
	int col; 
};
 
std::vector<Position> translate(std::vector<Position> tiles, int x,int y ); 
