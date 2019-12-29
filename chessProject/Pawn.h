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
	void promotion();
>>>>>>> a98e0baef0d25267bd8e3652e9e31565dcfd3a10
	void promotion(string indexes);
public:
	Pawn(bool color, Board* board);
	virtual codes checkValid(string indexes);
};