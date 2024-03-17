#pragma once 
class BlockRotation
{
public:
	int rotate_state;  
	int rotate_transalte;
	int maxRotationState;
	int maxRotateTranslate;
	BlockRotation(int x, int y) :rotate_state(0), rotate_transalte(0),
		maxRotationState(x),maxRotateTranslate(y) 
	{};
	BlockRotation() :rotate_state(0), rotate_transalte(0),
		maxRotationState(3), maxRotateTranslate(0)
	{};
	explicit BlockRotation(int x, int y, int maxro, int maxtra):
		rotate_state(x),rotate_transalte(y),
		maxRotationState(maxro),maxRotateTranslate(maxtra)
	{};
	void Translate(int x )
	{
		rotate_transalte=(rotate_transalte + x) % maxRotateTranslate;
	}
	void Rotate(int x,bool test )
	{
		if (test) {
			rotate_state = (rotate_state + x) % maxRotationState;
		}
		else
		{
			rotate_state = (rotate_state + x) % maxRotationState;
		}

		
	}
	bool operator==(const BlockRotation& another) ;
	
	bool operator<(const BlockRotation& another) const ;
	bool operator>(BlockRotation& another);
	bool operator<=(BlockRotation& another);


	
};