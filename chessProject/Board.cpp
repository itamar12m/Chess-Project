#include "Board.h"

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
	this->_turn = WHITE;
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
	this->_turn = WHITE;
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
				break;
			case 'R':
				this->_board[i][j] = new Rook(WHITE, this);
				break;/*
			case 'n':
				this->_board[i][j] = new Knight(BLACK, this);
				break;
			case 'N':
				this->_board[i][j] = new Knight(WHITE, this);
				break;*/
			case 'b':
				this->_board[i][j] = new Bishop(BLACK, this);
				break;
			case 'B':
				this->_board[i][j] = new Bishop(WHITE, this);
				break;
			case 'k':
				this->_board[i][j] = new King(BLACK, this);
				break;
			case 'K':
				this->_board[i][j] = new King(WHITE, this);
				break;
			case 'q':
				this->_board[i][j] = new Queen(BLACK, this);
				break;
			case 'Q':
				this->_board[i][j] = new Queen(WHITE, this);
				break;
			case 'p':
				this->_board[i][j] = new Pawn(BLACK, this);
				break;
			case 'P':
				this->_board[i][j] = new Pawn(WHITE, this);
				break;
			case '#':
				this->_board[i][j] = nullptr;
				break;
			default:
				// error
				this->_board[i][j] = nullptr;
				break;
			}
		}
		
	}
}

int Board::move(string indexes)
{
	if (this->getPiece(indexes[0], indexes[1]) == nullptr || this->getPiece(indexes[0], indexes[1])->getColor() != this->_turn)
	{
		return INVALID_NOT_PLAYER_PIECE_SRC;
	}
	if (this->getPiece(indexes[2], indexes[3]) != nullptr && this->getPiece(indexes[2], indexes[3])->getColor() == this->_turn)
	{
		return INVALID_PIECE_IN_DST;
	}
	int code = this->getPiece(indexes[0], indexes[1])->move(indexes);
	if (code == VALID_CHECK_MOVE || code == VALID_MOVE)
	{
		this->getPiece(indexes[2], indexes[3]) = this->getPiece(indexes[0], indexes[1]);
		this->getPiece(indexes[0], indexes[1]) = nullptr;
	}
	return code;
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