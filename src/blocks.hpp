#include"block.hpp"
#include"position.hpp"
#include<iostream> 


// la fonction move est utilisé pour que les blocs aparaissent en haut et au milieux du grid . 
// les valeurs de next_offset et les valeurs passées dans la fonctions move différent d'un bloc à un autre , en fonction de cellules occupées pour chaque bloc . 
class LBlock :public Block
{
public:
	LBlock()
	{
		id = 1;

		cells[0][1] = { Position(3,2),Position(2,2),Position(3,1),Position(3,0) };
		cells[0][0] = { Position(3,1),Position(2,1),Position(3,0),Position(3,-1) };

		cells[1][0] = { Position(3,0),Position(3,1),Position(2,0),Position(1,0) };
		cells[1][1] = { Position(3,0),Position(3,1),Position(2,0),Position(1,0) };

		cells[2][1] = { Position(3,2),Position(2,2),Position(2,1),Position(2,0) };
		cells[2][0] = { Position(3,1),Position(2,1),Position(2,0),Position(2,-1) };

		cells[3][0] = { Position(1,0),Position(1,1),Position(2,1),Position(3,1) };
		cells[3][1] = { Position(1,0),Position(1,1),Position(2,1),Position(3,1) };
		move(-2, -2);

		next_x_offset = 515;
		next_y_offset = 355;

	}



};
class JBlock : public Block
{
public:
	JBlock() {
		id = 2;
		cells[0][1] = { Position(3,2),Position(2,2),Position(2,1),Position(2,0) };
		cells[0][0] = { Position(3,1),Position(2,1),Position(2,0),Position(2,-1) };

		cells[1][0] = { Position(3,1),Position(3,0),Position(2,1),Position(1,1) };
		cells[1][1] = { Position(3,1),Position(3,0),Position(2,1),Position(1,1) };

		cells[2][1] = { Position(2,2),Position(2,0),Position(2,1),Position(3,0) };
		cells[2][0] = { Position(2,1),Position(2,-1),Position(2,0),Position(3,-1) };

		cells[3][1] = { Position(1,1),Position(1,0),Position(2,0),Position(3,0) };
		cells[3][0] = { Position(1,1),Position(1,0),Position(2,0),Position(3,0) };


		move(-1, -2);
		next_x_offset = 515;
		next_y_offset = 355;





	}

};
class IBlock : virtual public Block
{
public:

	IBlock()
	{
		id = 3;
		cells[1][0] = { Position(0,0),Position(1,0),Position(2,0),Position(3,0) };
		//cells[BlockRotation(0, 1, 2, 2)] = { Position(-3,0),Position(-2,0),Position(-1,0),Position(0,0) };
		cells[1][1] = { Position(0,0),Position(1,0),Position(2,0),Position(3,0) };


		cells[0][0] = { Position(3,-3),Position(3,-2),Position(3,-1),Position(3,0) };
		cells[0][1] = { Position(3,3),Position(3,1),Position(3,2),Position(3,0) };
		move(-3, 1);

		next_x_offset = 502;
		next_y_offset = 375;

	}
};

class OBlock :public Block
{
public:
	OBlock() {
		id = 4;

		cells[0][0] = { Position(3,0),Position(3,1),Position(2,0),Position(2,1) };
		cells[0][1] = { Position(3,0),Position(3,1),Position(2,0),Position(2,1) };


		move(-2, -1);
		next_x_offset = 505;
		next_y_offset = 355;
	}

};
class SBlock : public Block
{
public:
	SBlock() {
		id = 5;
		cells[0][1] = { Position(3,0),Position(3,1),Position(2,1),Position(2,2) };
		cells[0][0] = { Position(3,-1),Position(3,0),Position(2,0),Position(2,1) };

		cells[1][0] = { Position(1,0),Position(2,0),Position(2,1),Position(3,1) };
		cells[1][1] = { Position(1,0),Position(2,0),Position(2,1),Position(3,1) };
		move(-2, -2);
		next_x_offset = 522;
		next_y_offset = 355;
	}

};
class TBlock : public Block
{
public:
	TBlock()
	{
		id = 6;

		cells[0][1] = { Position(3,0),Position(3,1),Position(3,2),Position(2,1) };
		cells[0][0] = { Position(2,-1),Position(2,0),Position(2,1),Position(1,0) };

		cells[1][0] = { Position(3,0),Position(2,0),Position(1,0),Position(2,1) };
		cells[1][1] = { Position(3,0),Position(2,0),Position(1,0),Position(2,1) };

		cells[2][1] = { Position(2,0),Position(2,1),Position(2,2),Position(3,1) };
		cells[2][0] = { Position(2,-1),Position(2,0),Position(2,1),Position(3,0) };

		cells[3][0] = { Position(2,0),Position(3,1),Position(2,1),Position(1,1) };
		cells[3][1] = { Position(2,0),Position(3,1),Position(2,1),Position(1,1) };

		move(-2, -2);
		next_x_offset = 520;
		next_y_offset = 345;

	}

};
class ZBlock : public Block
{
public:
	ZBlock()
	{
		id = 7;

		cells[0][1] = { Position(2,0),Position(2,1),Position(3,1),Position(3,2) };
		cells[0][0] = { Position(2,-1),Position(2,0),Position(3,0),Position(3,1) };

		cells[1][0] = { Position(3,0),Position(2,0),Position(2,1),Position(1,1) };
		cells[1][1] = { Position(3,0),Position(2,0),Position(2,1),Position(1,1) };
		move(-2, -2);
		next_x_offset = 522;
		next_y_offset = 355;
	}

};
