#include "Board.h"

#define BLACK true
#define WHITE false

string Board::getMessageFromGraphics()
{
	return this->p.getMessageFromGraphics();
}

void Board::sendMessageToGraphics(string msg)
{
	p.sendMessageToGraphics(msg.c_str());
}

Board::Board()
{
	string boardStr = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0";
	this->init(boardStr);
	if (!p.connect())
	{
		cout << "Can't connect to the game!\n";
	}
	this->p.sendMessageToGraphics(boardStr.c_str());
}

Board::Board(string boardStr)
{
	this->init(boardStr);
	if (!p.connect())
	{
		cout << "Can't connect to the game!\n";
	}
	this->p.sendMessageToGraphics(boardStr.c_str());
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

int Board::move(string indexes)
{
	if (this->getPiece(indexes[0], indexes[1]) == nullptr)
	{
		return INVALID_NO_PIECE_SRC;
	}
	if (this->getPiece(indexes[2], indexes[3]) != nullptr)
	{
		return INVALID_PIECE_IN_DST;
	}
	if (indexes[0] == indexes[2] && indexes[1] == indexes[3])
	{
		return INVALID_SAME_DST_SRC;
	}
	return this->getPiece(indexes[0], indexes[1])->move(indexes);
}

Piece*& Board::getPiece(char letter, char num)
{
	int firstIndex = '0' + 8 - num;
	int secondIndex = letter - 'a';
	return this->_board[firstIndex][secondIndex];
}

void Board::changeTurn()
{
	this->_turn = this->_turn == WHITE ? this->_turn = BLACK : this->_turn = WHITE;
}

bool Board::isCheck()
{
	return false;
}

Board::~Board()
{
	p.close();
}