#pragma once
#include "Piece.h"
#include "Board.h"

class King : public Piece
{
public:
	King(bool color, Board* board);
	virtual int checkValid(string indexes);
};