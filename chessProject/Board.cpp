#include "Board.h"
#define BLACK true
#define WHITE false

Board::Board()
{
	this->init("rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0");
	
}

Board::Board(string boardStr)
{
	this->init(boardStr);
}

void Board::init(string boardStr)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			switch (boardStr[i*8 + j])
			{
			case 'r':
				this->_board[i][j] = new Rook(BLACK, this);
			case 'R':
				this->_board[i][j] = new Rook(WHITE, this);
				break;/*
			case 'n':
				this->_board[i][j] = new Knight(BLACK, this);
			case 'N':
				this->_board[i][j] = new Knight(WHITE, this);
				break;
			case 'B':
				this->_board[i][j] = new Bishop(BLACK, this);
			case 'b':
				this->_board[i][j] = new Bishop(WHITE, this);
				break;
			case 'k':
				this->_board[i][j] = new King(BLACK, this);
			case 'K':
				this->_board[i][j] = new King(WHITE, this);
				break;
			case 'q':
				this->_board[i][j] = new Queen(BLACK, this);
			case 'Q':
				this->_board[i][j] = new Queen(WHITE, this);
				break;
			case 'P':
				this->_board[i][j] = new Pawn(BLACK, this);
			case 'p':
				this->_board[i][j] = new Pawn(WHITE, this);
				break;
			case '#':
				this->_board[i][j] = nullptr;
				break;*/
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

Piece*& Board::getPiece(char letter, char num)
{
	int firstIndex = letter - 'a';
	int secondIndex = '0' + 8 - num;
	return this->_board[firstIndex][secondIndex];
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
