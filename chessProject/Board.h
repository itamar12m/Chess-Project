#pragma once
#include <iostream>
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Pawn.h"
#include "Knight.h"
#include "Piece.h"


using std::string;

class Board
{
private:
	Piece* _board[8][8];
	bool _turn;
public:
	Board();
	Board(string boardStr);
	void init(string boardStr);
	void move(string indexes);
	Piece*& getPiece(char letter, char num);
	void changeTurn();
	bool isCheck();
	~Board();
};