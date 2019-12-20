#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	virtual int move(string indexes);
};