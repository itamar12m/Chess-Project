#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	virtual int move(string indexes);
};