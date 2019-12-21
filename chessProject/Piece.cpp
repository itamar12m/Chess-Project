#include "Piece.h"
#include "Board.h"

Piece::Piece(bool color, Board* board) : _color(color), _board(board)
{
}

bool Piece::getColor()
{
	return this->_color;
}

int Piece::checkWayForRook(string indexes, Board* board)
{
	int difference;
	if (indexes[0] != indexes[2]) // horizontal
	{
		difference = abs((int)(indexes[2] - indexes[0]));
		for (int i = 1; i < difference; i++)
		{
			if (board->getPiece(indexes[0] + i, indexes[1]) != nullptr)
			{
				return INVALID_PIECE_MOVE;
			}
		}
	}
	else // vertical
	{
		difference = abs((int)(indexes[3] - indexes[1]));
		for (int i = 1; i < difference; i++)
		{
			if (board->getPiece(indexes[0], indexes[1] + (indexes[1] > indexes[3] ? -i : i)) != nullptr)
			{
				/*
				the shorted if:
				if indexes[1] is 8 and indexes[3] is 5, so I want to go down..
				if the opposite, I want to go up.
				*/
				return INVALID_PIECE_MOVE;
			}
		}
	}
	return VALID_MOVE;
}

int Piece::checkWayForBishop(string indexes, Board* board)
{
	for (int i = 1; i < abs(indexes[0] - indexes[2]); i++)
	{
		if (board->getPiece(indexes[2] + (indexes[0] > indexes[2] ? -i : i), indexes[3] + (indexes[1] > indexes[3] ? -i : i)) != nullptr)
		{
			return INVALID_PIECE_MOVE;
		}
	}
	return VALID_MOVE;
}

Piece::~Piece()
{
}