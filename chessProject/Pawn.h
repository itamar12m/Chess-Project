#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
	bool checkFirst();
	virtual int move(string indexes);
};
