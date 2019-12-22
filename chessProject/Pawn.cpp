#include "Pawn.h"

bool Pawn::checkFirst(string indexes)
{
	if (indexes[1] == '7' && _color == BLACK ||(indexes[1] == '1' && _color == WHITE))
	{
		return true;
	}
	return false;
}

bool Pawn::isCapture(string indexes)
{
	if (_board->getPiece(indexes[2], indexes[3]) != nullptr &&
		((indexes[1] + 1 == indexes[3] && indexes[0] -1 == indexes[2]) ||
		(indexes[1] -1 == indexes[3] && indexes[0] +1 == indexes[2])))
	{
		return true;
	}
	return false;
}

int Pawn::move(string indexes)
{
	if (checkFirst(indexes))
	{
		if (_color == BLACK && (indexes[2] + 2 == indexes[0] || indexes[2] + 1 == indexes[0])) {
			return VALID_MOVE;
		}
		if (_color == WHITE && (indexes[2] - 2 == indexes[0] || indexes[2] - 1 == indexes[0]))
		{
			return VALID_MOVE;
		}
	}
	else if (isCapture(indexes))
	{
		return VALID_MOVE;
	}
	else if (!((_color == BLACK && indexes[3] + 1 == indexes[1]) ||(_color == WHITE && indexes[3] -1 == indexes[1])))
	{
		return INVALID_PIECE_MOVE;
	}
	return VALID_MOVE;
}
