#pragma once
#include <iostream>
#include "stdafx.h"

enum codes
{
VALID_MOVE,
VALID_CHECK_MOVE,
INVALID_NOT_PLAYER_PIECE_SRC,
INVALID_PIECE_IN_DST,
INVALID_SELF_CHECK_MOVE,
INVALID_WRONG_INDEX,
INVALID_PIECE_MOVE,
INVALID_SAME_DST_SRC,
VALID_MATE
};

using std::string;

class Board;

class Piece
{
public:
	Piece(bool color, Board* board);
	virtual codes checkValid(string indexes) = 0;
	bool getColor();
	virtual ~Piece();

protected:
	codes checkWayForRook(string indexes);
	codes checkWayForBishop(string indexes);
	bool _color;
	Board* _board;
};
