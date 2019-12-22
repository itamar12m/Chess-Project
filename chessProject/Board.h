#pragma once
#include <iostream>
#include "Pipe.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Pawn.h"
#include "Knight.h"
#include "Piece.h"

#define BLACK true
#define WHITE false

using std::string;
using std::cout;

class Board
{
private:
	Piece* _board[8][8];
	bool _turn;
	Pipe p;
public:
	Board();
	Board(string boardStr);
	string getMessageFromGraphics();
	void sendMessageToGraphics(string msg);
	void init(string boardStr);
	int move(string indexes);
	Piece*& getPiece(char letter, char num);
	void changeTurn();
	bool isCheck();
	~Board();
};