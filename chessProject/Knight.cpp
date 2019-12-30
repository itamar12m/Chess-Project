#include "Knight.h"

Knight::Knight(color color, Board* board) : Piece(color, board)
{
	this->_type = 'N';
}

codes Knight::checkValid(string indexes)
{
	if (abs((int)(indexes[0]-indexes[2])) == 1 && abs((int)(indexes[1] - indexes[3])) == 2 || 
		abs((int)(indexes[0] - indexes[2])) == 2 && abs((int)(indexes[1] - indexes[3])) == 1)
	{
		return VALID_MOVE;
	}
	return INVALID_PIECE_MOVE;
}