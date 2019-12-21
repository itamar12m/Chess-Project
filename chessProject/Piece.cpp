#include "Piece.h"

Piece::Piece(bool color, Board* board) : _color(color), _board(board)
{
}

bool Piece::getColor()
{
	return this->_color;
}

Piece::~Piece()
{
}