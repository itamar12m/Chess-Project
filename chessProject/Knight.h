#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(bool color, Board* board);
	virtual int move(string indexes);
};