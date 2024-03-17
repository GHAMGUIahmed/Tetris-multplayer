#include "position.hpp"
Position::Position(int row, int col) :row(row), col(col){}

std::vector<Position> translate(std::vector<Position> tiles, int x,int y)
{
	std::vector<Position> tilesTranslated;
	for (Position item : tiles)
	{
		tilesTranslated.push_back(Position(item.row + x, item.col+y));

	}
	return tilesTranslated;
}


