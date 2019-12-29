#pragma once
#include "Piece.h"
#include "Board.h"

class Pawn : public Piece
{
private:
	bool checkFirst(string indexes);
	bool isCapture(string indexes);
	int checkWayForPawn(string indexes);
<<<<<<< HEAD
=======
	void promotion(string indexes);
>>>>>>> a399c78607eaab7d358e2985478f5cc8d61f2f2a
public:
	Pawn(bool color, Board* board);
	virtual codes checkValid(string indexes);
};
