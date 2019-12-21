#pragma once
#include "Piece.h"
#include "Board.h"

class Queen : public Piece
{
public:
	Queen(bool color, Board* board);
	virtual int move(string indexes);
};