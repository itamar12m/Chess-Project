#include "Pawn.h"

bool Pawn::checkFirst(string indexes)
{
	if (indexes[1] == '7' && _color == BLACK ||(indexes[1] == '2' && _color == WHITE))
	{
		return true;
	}
	return false;
}

bool Pawn::isCapture(string indexes)
{
	if (_board->getPiece(indexes[2], indexes[3]) != nullptr &&
		abs((int)(indexes[0] - indexes[2])) == 1 &&
		abs((int)(indexes[1] - indexes[3])) == 1 &&
		(_board->getPiece(indexes[0], indexes[1])->getColor() == WHITE && indexes[3]-indexes[1] == 1 ||
			_board->getPiece(indexes[0], indexes[1])->getColor() == BLACK && indexes[3] - indexes[1] == -1))
	{
		return true;
	}
	return false;
}

int Pawn::checkWayForPawn(string indexes)
{
	if (_board->getPiece(indexes[2], indexes[3]) != nullptr ||
		(_color == BLACK && _board->getPiece(indexes[2], indexes[3] + 1) != nullptr && indexes[3] + 1 != indexes[1] ||
		(_color == WHITE && _board->getPiece(indexes[2], indexes[3] - 1) != nullptr && indexes[3] - 1 != indexes[1])))
	{
		return false;
	}
	return true;
}

Pawn::Pawn(bool color, Board* board) : Piece(color, board)
{
}

int Pawn::move(string indexes)
{
	if (checkFirst(indexes))
	{
		if (_color == BLACK && (indexes[3] + 2 == indexes[1] || indexes[3] + 1 == indexes[1]) && indexes[0] == indexes[2] && checkWayForPawn(indexes)) {
			return VALID_MOVE;
		}
		if (_color == WHITE && (indexes[3] - 2 == indexes[1] || indexes[3] - 1 == indexes[1]) && indexes[0] == indexes[2] && checkWayForPawn(indexes))
		{
			return VALID_MOVE;
		}
	}
	if (isCapture(indexes))
	{
		return VALID_MOVE;
	}
	else if (((_color == BLACK && indexes[3] + 1 == indexes[1] && indexes[0] == indexes[2]) ||
		(_color == WHITE && indexes[3] -1 == indexes[1] && indexes[0] == indexes[2])) && checkWayForPawn(indexes))
	{
		return VALID_MOVE;
	}
	return INVALID_PIECE_MOVE;
}
