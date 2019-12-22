#pragma once
#include "Piece.h"
#include "Board.h"

class Pawn : public Piece
{
private:
	bool checkFirst(string indexes);
	bool isCapture(string indexes);
public:
	virtual int move(string indexes);
};
