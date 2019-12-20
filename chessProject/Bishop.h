#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	virtual int move(string indexes);
};