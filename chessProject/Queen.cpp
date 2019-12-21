#include "Queen.h"

Queen::Queen(bool color, Board* board) : Piece(color, board)
{
}

int Queen::move(string indexes)
{
	if (abs((int)indexes[0] - (int)indexes[2]) != abs((int)indexes[1] - (int)indexes[3]) &&
		indexes[0] != indexes[2] && indexes[1] != indexes[3])
	{
		return INVALID_PIECE_MOVE;
	}

	return 0;
}