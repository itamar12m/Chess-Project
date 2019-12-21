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
	this->_board->getPiece(indexes[2], indexes[3]) = this->_board->getPiece(indexes[0], indexes[1]);
	this->_board->getPiece(indexes[0], indexes[1]) = nullptr;
	return VALID_MOVE;
}