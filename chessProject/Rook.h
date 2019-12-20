#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(bool color, Board* board);
	virtual int move(string indexes);
};