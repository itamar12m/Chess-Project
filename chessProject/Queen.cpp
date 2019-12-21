#include "Queen.h"

Queen::Queen(bool color, Board* board) : Piece(color, board)
{
}

int Queen::move(string indexes)
{
	bool isBishopMove = indexes[0] != indexes[2] && indexes[1] != indexes[3]; // or it's an error
	if (abs((int)(indexes[0] - indexes[2])) != abs((int)(indexes[1] - indexes[3])) && isBishopMove)
	{
		return INVALID_PIECE_MOVE;
	}
	if (isBishopMove)
	{
		return this->checkWayForBishop(indexes, this->_board);
	}
	else // rook move
	{
		return this->checkWayForRook(indexes, this->_board);
	}
}
