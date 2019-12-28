#pragma once
#include "Piece.h"
#include "Board.h"

class Rook : public Piece
{
public:
	Rook(bool color, Board* board);
	virtual codes checkValid(string indexes);
};