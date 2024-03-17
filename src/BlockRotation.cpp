#pragma once 
#include"BlockRotation.hpp"

bool BlockRotation::operator==(const BlockRotation& another)
{
	
		return(another.maxRotateTranslate == maxRotateTranslate) && (another.maxRotationState == maxRotationState)
			&& (another.rotate_state == rotate_state) && (another.rotate_transalte == rotate_transalte);
	
}

bool BlockRotation::operator<( const BlockRotation& another) const 

	{
		return (rotate_state < another.rotate_state) && (rotate_transalte < another.rotate_transalte);
	}





