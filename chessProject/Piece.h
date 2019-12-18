#pragma once
#include <iostream>
#include "Board.h"

using std::string;

class Board;

class Piece
{
public:
	Piece(bool color, Board* board);
	int move(string toMove);
	~Piece();

protected:
	//metod:
	int checkVallid(string toMove);

	//fildes:
	bool _color;
	Board* _board;
};

Piece::Piece(bool color, Board* board) : _color(color), _board(board)
{
}

Piece::~Piece()
{
}

