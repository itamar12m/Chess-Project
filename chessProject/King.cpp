#include "King.h"

King::King(bool color, Board* board) : Piece(color, board)
{
}

int King::move(string indexes)
{
	if (indexes[2] + 1 == indexes[0] || indexes[2] - 1 == indexes[0] || indexes[2] == indexes[0] ||
		indexes[3] + 1 == indexes[1] || indexes[3] - 1 == indexes[1] || indexes[3] == indexes[1])
	{
		return INVALID_PIECE_MOVE;
	}
	return 0;
}
