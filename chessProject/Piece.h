#pragma once
#include <iostream>
#include "Board.h"

class Board;

class Piece
{
public:
	Piece(bool color, Board* board);
	virtual int move(string toMove);
	virtual int checkValid(string toMove);
	virtual ~Piece();

protected:
	bool _color;
	Board* _board;
};
