#include "Bishop.h"

Bishop::Bishop(bool color, Board* board) : Piece(color, board)
{
}

int Bishop::move(string indexes)
{
	if (abs((int)indexes[0] - (int)indexes[2]) != abs((int)indexes[1] - (int)indexes[3]))
	{
		return INVALID_PIECE_MOVE;
	}
	return VALID_MOVE;
}