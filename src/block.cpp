#include"block.hpp"
#include<iostream>

Block::Block()
{
	cell_size = 35;
	colors = GetCellColors();
	rowOffset = 0;
	colOffset = 5;
	rotationState = 0;
	initialiserPivot();
	

	
} 

void Block::draw(sf::RenderTexture& texture , int offsetx, int offsety, bool stop,sf::Clock& clock) 
{
	std::vector<Position> tiles = get_cell_postion();
	for (Position item : tiles )
	{ 
		sf::RectangleShape rectangle;  
		rectangle.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));
		rectangle.setPosition(item.col * cell_size + offsetx, item.row * cell_size + offsety);
		colors[id].a = 255;

		rectangle.setFillColor(colors[id]);
		
		texture.draw(rectangle);


	}
	if (stop) {
		for (Position item : tiles)
		{
			sf::RectangleShape rectangle1;
			rectangle1.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));
			rectangle1.setPosition(item.col * cell_size + offsetx, item.row * cell_size + offsety);
			colors[id].a = 100;


			rectangle1.setFillColor(colors[0]);

			

			while (clock.getElapsedTime().asMilliseconds() > 100)
			{
				drawtra(texture, offsetx, offsety);
				clock.restart();

			}
			sf::RectangleShape rectangle2;
			rectangle2.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));
			rectangle2.setPosition(item.col * cell_size + offsetx, item.row * cell_size + offsety);
			colors[id].a = 100;


			rectangle2.setFillColor(colors[id]);

			texture.draw(rectangle2);
		}


		
	}

	
}


void Block::drawtra(sf::RenderTexture& texture , int offsetx, int offsety)
{
	std::vector<Position> tiles = get_cell_postion();
	for (Position item : tiles)
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));
		rectangle.setPosition(item.col * cell_size + offsetx, item.row * cell_size + offsety);
		rectangle.setFillColor(colors[0]);
		texture.draw(rectangle);


	}

}


void Block::move(int rows , int cols )

{
	rowOffset += rows;
	colOffset += cols;
	initialiserPivot();
	
	
	

	
} 
std::vector<Position> Block::get_cell_postion()
{  
	std::vector<Position> tiles = cells[rotationState][pivot];
	std::vector<Position> movedTiles; 
	for (Position item : tiles)
	{ 
		Position newPos = Position(item.row + rowOffset, item.col + colOffset);
		movedTiles.push_back(newPos);
	}
	
	return movedTiles;

	 
}  

void Block::Rotate(int i )
{
	
	if (i == 1) {
		rotationState=(rotationState+1)%cells.size();
	} 
	if (i == -1)
	{
		
		rotationState = (rotationState -1) %cells.size();
	}
	
}

int Block::getLastRow()
{
	std::vector<Position> tiles = get_cell_postion();
	int max = 0; 
	for(Position item : tiles )
	{
		if (item.row > max) max = item.row;
 	 } 
	return max; 
}

void Block::initialiserPivot()
{ 
	if (colOffset > 4)
	{
		pivot = 0;
	}
	else 
	{

	pivot = 1;
	}
}






int max_col(std::vector<Position> curentCell)
{
	 int max = 0;
	for(Position item : curentCell)
	{
		if (item.col > max) max = item.col;

	}
	return max;
}


int min_row(std::vector<Position> currentCell)
{
	int min = 15; 
	for(Position item : currentCell )
	{
		if (item.row < min) min = item.row;
	}
	return min;
}


int min_col(std::vector<Position> curentCell)
{
	int max = 0; 
	for (Position item : curentCell) {
		if (item.col > max) max = item.col;
	} 
	return max;
}
