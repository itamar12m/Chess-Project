#include "Bishop.h"

Bishop::Bishop(color color, Board* board) : Piece(color, board)
{
	this->_type = 'B';
}

codes Bishop::checkValid(string indexes)
{
	if (abs((int)(indexes[0] - indexes[2])) != abs((int)(indexes[1] - indexes[3])))
	{
		return INVALID_PIECE_MOVE;
	}
	return this->checkWayForBishop(indexes); // I did a function because of the queen
}