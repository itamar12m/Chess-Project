#pragma once
#include "Piece.h"
#include "Board.h"

class Queen : public Piece
{
public:
	Queen(color color, Board* board);
	virtual codes checkValid(string indexes);
};