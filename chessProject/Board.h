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

using std::string;

class Board
{
private:
	Piece* _board[8][8];
	color _turn;
	Pipe _p;
	string _whiteKing;
	string _blackKing;
public:
	Board();
	void printBoard();
	codes checkValid(string indexes);
	codes checkBasicValid(string indexes);
	bool getTurn() const;
	string getMessageFromGraphics();
	void sendMessageToGraphics(string msg);
	void setKingPosition(string pos, color color);
	codes move(string indexes);
	Piece*& getPiece(char letter, char num);
	void changeTurn();
	bool isCheck(color color);
	bool isMate(color turn);
	codes castling(string indexes);
	string promotion(string indexes);
	string makeBoardStr(color turn);
	~Board();
};