#include "Rook.h"
#include "Board.h"

Rook::Rook(bool color, Board* board) : Piece(color, board)
{
}

int Rook::move(string indexes)
{
	int difference;
	if (indexes[0] != indexes[2] && indexes[1] != indexes[3])
	{
		return INVALID_PIECE_MOVE;
	}
	if (indexes[0] != indexes[2]) // horizontal
	{
		difference = abs(int(indexes[2] - indexes[0]));
		for (int i = 1; i < difference; i++)
		{
			if (_board->getPiece(indexes[0], indexes[1]+i) != nullptr)
			{
				return INVALID_PIECE_MOVE;
			}
		}
	}
	else // vertical
	{
		difference = abs(int(indexes[3] - indexes[1]));
		for (int i = 1; i < difference; i++)
		{
			if (_board->getPiece(indexes[0], indexes[1] + i) != nullptr)
			{
				return INVALID_PIECE_MOVE;
			}
		}
	}
	_board->getPiece(indexes[2], indexes[3]) = _board->getPiece(indexes[0], indexes[1]);
	// (*_board).getPiece(indexes[2], indexes[3]) = (*_board).getPiece(indexes[0], indexes[1]);
	_board->getPiece(indexes[0], indexes[1]) = nullptr;
	return VALID_MOVE;
}