#pragma once
#include "Piece.h"
#include "Board.h"

class Pawn : public Piece
{
private:
	bool checkFirst(string indexes);
	bool isCapture(string indexes);
	int checkWayForPawn(string indexes);
public:
	Pawn(bool color, Board* board);
	virtual int checkValid(string indexes);
};
