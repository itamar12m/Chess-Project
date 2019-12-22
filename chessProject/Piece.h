#pragma once
#include <iostream>
#include "stdafx.h"

#define VALID_MOVE 0
#define VALID_CHECK_MOVE 1
#define INVALID_NOT_PLAYER_PIECE_SRC 2
#define INVALID_PIECE_IN_DST 3
#define INVALID_SELF_CHECK_MOVE 4
#define INVALID_INDEXES 5
#define INVALID_PIECE_MOVE 6
#define INVALID_SAME_DST_SRC 7
#define VALID_MATE 8

using std::string;

class Board;

class Piece
{
public:
	Piece(bool color, Board* board);
	virtual int move(string indexes) = 0;
	bool getColor();
	virtual ~Piece();

protected:
	int checkWayForRook(string indexes);
	int checkWayForBishop(string indexes);
	bool _color;
	Board* _board;
};
