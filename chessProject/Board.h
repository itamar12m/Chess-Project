#pragma once
#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Piece;
class Board
{
protected:
	Piece* _board[8][8];
	bool turn;
public:
	Board();
	Board(string boardStr);
	void init(string boardStr);
	void move(string indexes);
	//Piece* operator[][](char letter, char num);

};