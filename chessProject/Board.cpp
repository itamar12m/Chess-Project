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
			{/*
			case 'r':
			case 'R':
				this->_board[i][j] = new Rook();
				break;
			case 'n':
			case 'N':
				this->_board[i][j] = new Knight();
				break;
			case 'B':
			case 'b':
				this->_board[i][j] = new Bishop();
				break;
			case 'k':
			case 'K':
				this->_board[i][j] = new King();
				break;
			case 'q':
			case 'Q':
				this->_board[i][j] = new Queen();
				break;
			case 'P':
			case 'p':
				this->_board[i][j] = new Pawn();
				break;*/
			case '#':
				this->_board[i][j] = nullptr;
				break;
			default:
				// error
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
