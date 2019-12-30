#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(color color, Board* board);
	virtual codes checkValid(string indexes);
};