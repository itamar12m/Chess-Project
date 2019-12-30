#pragma once
#include "Piece.h"
#include "Board.h"

class Rook : public Piece
{
public:
	Rook(color color, Board* board);
	virtual codes checkValid(string indexes);
};