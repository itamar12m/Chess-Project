#pragma once
#include <iostream>
#include "stdafx.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Piece;

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
	Piece* getPiece(char letter, char num);
	void changeTurn();
	bool isCheck();
	~Board();
};