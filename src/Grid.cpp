#include"Grid.hpp"
#include<iostream>
#include"colors.hpp"
Grid::Grid()
{
	numRows =22;
	numCols = 10;
	cell_size = 35; 
	initialiser();
	colors = GetCellColors();
}
void Grid::initialiser()
{ 
	for (int row = 0; row <numRows ;row++)
	{ for (int col=0;col<numCols;col++)
	{
		grid[row][col] = 0;
	}
	}

} 
void Grid::print()
{for (int row =0 ; row<numRows;row++)
{for (int col=0;col<numCols;col++)
{
	std::cout << grid[row][col]<<" ";
}
std::cout<<std::endl;
}
} 
/*std::vector<sf::Color> Grid::Get_Cell_Color()
{ 
	sf::Color darkGrey(26,31,40,255 );
	sf::Color green= sf::Color::Green;
	sf::Color red = sf::Color::Red;
	sf::Color orange(226,116,17,255);
	sf::Color yellow = sf::Color::Yellow;
	sf::Color purple (26,31,40,255);
	sf::Color cyan = sf::Color::Cyan;
	sf::Color blue= sf::Color::Blue;
	return{ darkGrey,green,red,orange,yellow,purple,cyan,blue };

} */
void Grid::draw(sf::RenderTexture& render, std::vector<Position> blockPlace)
{
	for (int row =0; row<numRows;row++)
	{ 
		for (int col=0;col<numCols;col++)
	{
		int cell_value = grid[row][col];  
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));
		rectangle.setPosition(col * cell_size+11, row * cell_size+11);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color::Cyan);
		rectangle.setFillColor(colors[cell_value]);
		render.draw(rectangle);
		

	}
	}
	std::vector<Position> WinYt7at = WinyjemYt7at(blockPlace, getLastRow(blockPlace)); 
	for(Position item:WinYt7at)
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(cell_size - 1, cell_size - 1));
		rectangle.setPosition(item.col * cell_size +11, item.row * cell_size +11);
		rectangle.setOutlineThickness(1);
		rectangle.setOutlineColor(sf::Color::Magenta);
		rectangle.setFillColor(colors[0]);
		render.draw(rectangle);
		


	}

} 
bool Grid::IsCellOutside(int row , int col)
{
	if (row >= 0 && row < numRows && col >= 0 && col < numCols) return false; 
	return true;
} 

bool Grid::IsCellEmpty(int row , int col )
{ 
	if (grid[row][col] == 0) return true;
	else return false; 
} 
bool Grid::IsRowFull(int row  )
{ 
	for (int column=0;column<numCols;column++)
	{
		if (grid[row][column] == 0) return false; 
	} 
	return true; 

} 



void Grid::ClearRow(int row)

{


	for (int col = 0; col < numCols; col++)
	{
		grid[row][col] = 0;
	}
}
		
 void Grid::MoveRowDown(int row , int number) 
 {
	 for(int col=0;col<numCols;col++)
	 {
		 grid[row + number][col] = grid[row][col];
		 grid[row][col] = 0;
	 }
 }

 // cette fonction serve à connaitre la position possible ou on peut dessiner le shadow 
 std::vector<Position> Grid::WinyjemYt7at(std::vector<Position> tiles, int i) // o5or ligne de bloc 
 {
	 
	 std::vector<Position> cuurent = tiles;
	 std::vector<Position> translated = translate(cuurent, 1,0);
	 int j = getLastRow(cuurent);
	 
	 while (j < numRows-1)
	 {
		 for (Position item : translated)
		 {
			 if (!IsCellEmpty(item.row, item.col))
			 {
				 return cuurent;
			 }
		 }
		 cuurent = translated;
		 translated = translate(cuurent, 1,0);
		 j = getLastRow(cuurent);


	 }
 }

	
	
 




	 
 

 int Grid::ClearFullRows()
 {
	 int completed = 0; 
	 for(int row=numRows-1;row>=0;row--)
	 { 
		 if(IsRowFull(row))
		 { 
			 ClearRow(row);
			 completed++;
		 }
		 else if(completed>0)
		 {
			 MoveRowDown(row, completed);
		 }
	 }
	 return completed;
 }

 int Grid::LastRowGrid()
 { 
	
	 for(int row =numRows-1; row<0;row--)
	 {
		 int col = 0;
		 while(col<numCols)
		 {
			 if(!IsCellEmpty(row,col))
			 {
				 break;

			 }
			 col++;
		 }
		 if (col == numCols - 1) return row;
		 
	 }
 }

 int getLastRow(std::vector<Position> tiles)
 {
	 int max =0 ;
	 for (Position item : tiles)
	 {
		 if (item.row > max) max = item.row;
	 }
	 return max;
 }
