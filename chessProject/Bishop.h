#pragma once
#include "Piece.h"
#include "Board.h"

class Bishop : public Piece
{
public:
	Bishop(bool color, Board* board);
	virtual codes checkValid(string indexes);
};