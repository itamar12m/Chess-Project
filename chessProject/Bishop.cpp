#include "Bishop.h"

Bishop::Bishop(bool color, Board* board) : Piece(color, board)
{
}

int Bishop::checkValid(string indexes)
{
	if (abs((int)(indexes[0] - indexes[2])) != abs((int)(indexes[1] - indexes[3])))
	{
		return INVALID_PIECE_MOVE;
	}
	return this->checkWayForBishop(indexes); // I did a function because of the queen
}