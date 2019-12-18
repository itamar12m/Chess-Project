#include "Board.h"

Board::Board()
{
	this->init("rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0");
	
}

Board::Board(string boardStr)
{
}

void Board::init(string boardStr)
{
	for (size_t i = 0; i < 64; i++)
	{
		switch (boardStr[i])
		{
		case 'r' || 'R':
			this->_board[i] = new Rook();
		default:
			break;
		}
	}
}

void Board::move(string indexes)
{
}

Piece* Board::getPiece(char letter, char num)
{
	return nullptr;
}

void Board::changeTurn()
{
}

bool Board::isCheck()
{
	return false;
}

Board::~Board()
{
}
