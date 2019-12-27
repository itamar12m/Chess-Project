#pragma once
#include <iostream>
#include <vector>
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

class Board
{
private:
	Piece* _board[8][8];
	bool _turn;
	Pipe _p;
	string _whiteKing;
	string _blackKing;
	vector<string> findWay(string indexes);
public:
	Board();
	int checkValid(string indexes);
	bool getTurn() const;
	string getMessageFromGraphics();
	void printBoard();
	void sendMessageToGraphics(string msg);
	void setKingPosition(string pos, bool color);
	void init(string boardStr);
	int move(string indexes);
	Piece*& getPiece(char letter, char num);
	void changeTurn();
	bool isCheck(bool color);
	bool isCheckMate(bool color);
	~Board();
};