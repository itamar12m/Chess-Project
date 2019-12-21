#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(bool color, Board* board);
	virtual int move(string indexes);
};