#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	virtual int move(string indexes);
};