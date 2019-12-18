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
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			switch (boardStr[i*8 + j])
			{
			case 'r' || 'R':
				this->_board[i][j] = new Rook();
			default:
				break;
			}
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
