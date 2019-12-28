#include "Rook.h"

Rook::Rook(bool color, Board* board) : Piece(color, board)
{
}

codes Rook::checkValid(string indexes)
{
	if (indexes[0] != indexes[2] && indexes[1] != indexes[3])
	{
		return INVALID_PIECE_MOVE;
	}
	return this->checkWayForRook(indexes); // I did a function because of the queen
}