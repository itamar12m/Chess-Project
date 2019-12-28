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

enum checkMate
{
	NOTHING = -1,
	CHECK,
	MATE
};

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
	codes checkValid(string indexes);
	bool getTurn() const;
	string getMessageFromGraphics();
	void printBoard();
	void sendMessageToGraphics(string msg);
	void setKingPosition(string pos, bool color);
	void init(string boardStr);
	codes move(string indexes);
	Piece*& getPiece(char letter, char num);
	void changeTurn();
	checkMate isCheckMate(bool color);
	bool isMate(vector<string> way, bool turn);
	~Board();
};