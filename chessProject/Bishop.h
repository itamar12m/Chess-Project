#pragma once
#include "Piece.h"
#include "Board.h"

class Bishop : public Piece
{
public:
	Bishop(color color, Board* board);
	virtual codes checkValid(string indexes);
};