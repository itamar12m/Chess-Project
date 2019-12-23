#include "King.h"

King::King(bool color, Board* board) : Piece(color, board)
{
	this->_board->setKingPosition("e8", BLACK);
	this->_board->setKingPosition("e1", WHITE);
}

int King::move(string indexes)
{
	if (abs((int)(indexes[0] - indexes[2])) == 1 && abs((int)(indexes[1] - indexes[3])) == 1 ||
		abs((int)(indexes[0] - indexes[2])) == 1 && abs((int)(indexes[1] - indexes[3])) == 0 ||
		abs((int)(indexes[0] - indexes[2])) == 0 && abs((int)(indexes[1] - indexes[3])) == 1)
	{
		this->_board->setKingPosition(indexes.substr(0, 2), this->_board->getPiece(indexes[0], indexes[1])->getColor());
		return VALID_MOVE;
	}
	return INVALID_PIECE_MOVE;
}