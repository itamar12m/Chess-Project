#include "Board.h"

string Board::getMessageFromGraphics()
{
	return this->_p.getMessageFromGraphics();
}

void Board::sendMessageToGraphics(string msg)
{
	this->_p.sendMessageToGraphics(msg.c_str());
}

void Board::setKingPosition(string pos, bool color)
{
	if (color == WHITE)
	{
		this->_whiteKing = pos;
	}
	else
	{
		this->_blackKing = pos;
	}
}

Board::Board()
{
	this->_turn = WHITE;
	string boardStr = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0";
	this->init(boardStr);
	if (!_p.connect())
	{
		cout << "Can't connect to the game!\n";
	}
	this->_p.sendMessageToGraphics(boardStr.c_str());
}

void Board::moveBack(string indexes)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			string str = typeid(*this->_board[i][j]).name();
			if (str != "Pawn")
			{
				this->move(indexes.substr(2, 2) + indexes.substr(0, 2));
			}
		}
	}
}

int Board::checkValid(string indexes)
{
	if (this->getPiece(indexes[0], indexes[1]) == nullptr || this->getPiece(indexes[0], indexes[1])->getColor() != this->_turn)
	{
		return INVALID_NOT_PLAYER_PIECE_SRC;
	}
	if (this->getPiece(indexes[2], indexes[3]) != nullptr && this->getPiece(indexes[2], indexes[3])->getColor() == this->_turn)
	{
		return INVALID_PIECE_IN_DST;
	}
	if (this->isCheck(_turn))
	{
		this->moveBack(indexes);
		return INVALID_SELF_CHECK_MOVE;
	}
	if (this->isCheck(!_turn))
	{
		return VALID_CHECK_MOVE;
	}
	if (indexes[0] == indexes[2] && indexes[1] == indexes[3]) // it's needed because of the function
		// of isCheck - it checks also the king itself
	{
		return INVALID_SAME_DST_SRC;
	}
	return this->getPiece(indexes[0], indexes[1])->checkValid(indexes);
}

bool Board::getTurn() const
{
	return this->_turn;
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
				break;
			case 'n':
				this->_board[i][j] = new Knight(BLACK, this);
				break;
			case 'N':
				this->_board[i][j] = new Knight(WHITE, this);
				break;
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
	int code = this->checkValid(indexes);

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
	this->_turn = this->_turn == WHITE ? BLACK : WHITE;
}

bool Board::isCheck(bool color)
{
	for (char i = 'a'; i <= 'h'; i++)
	{
		for (char j = '1'; j <= '8'; j++)
		{
			if (this->checkValid(string(1, i) + string(1, j) +
				(color == WHITE ? _whiteKing : _blackKing)) == VALID_MOVE)
			{
				return true;
			}
		}
	}
	return false;
}

Board::~Board()
{
	_p.close();
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (this->_board[i][j] != nullptr)
			{
				delete this->_board[i][j];
			}
		}
	}
}