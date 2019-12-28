#include "Board.h"

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

void Board::init(string boardStr)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			switch (boardStr[i * 8 + j])
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

codes Board::checkValid(string indexes)
{
	if (indexes[0] > 'h' || indexes[0] < 'a' || indexes[1] > '8' || indexes[1] < '1' ||
		indexes[2] > 'h' || indexes[2] < 'a' || indexes[3] > '8' || indexes[3] < '1')
	{
		return INVALID_WRONG_INDEX;
	}
	if (this->getPiece(indexes[0], indexes[1]) == nullptr || this->getPiece(indexes[0], indexes[1])->getColor() != this->_turn)
	{
		return INVALID_NOT_PLAYER_PIECE_SRC;
	}
	if (this->getPiece(indexes[2], indexes[3]) != nullptr && this->getPiece(indexes[2], indexes[3])->getColor() == this->_turn)
	{
		return INVALID_PIECE_IN_DST;
	}
	if (indexes[0] == indexes[2] && indexes[1] == indexes[3]) // it's needed because of the function
		// of isCheck - it checks also the king itself
	{
		return INVALID_SAME_DST_SRC;
	}

	codes code = this->getPiece(indexes[0], indexes[1])->checkValid(indexes);
	string tmpPlaceKing = (_turn == WHITE ? _whiteKing : _blackKing);
	Piece* copy;
	if (code == VALID_MOVE)
	{
		copy = this->getPiece(indexes[2], indexes[3]);
		this->getPiece(indexes[2], indexes[3]) = this->getPiece(indexes[0], indexes[1]);
		this->getPiece(indexes[0], indexes[1]) = nullptr;
	}
	else
	{
		return code;
	}
	if (this->isCheckMate(this->_turn) == CHECK) // check on the current player
	{
		return INVALID_SELF_CHECK_MOVE;
	}
	else if (this->isCheckMate(!this->_turn) == CHECK) // check on the other player
	{
		return VALID_CHECK_MOVE;
	}
	else if (this->isCheckMate(!this->_turn) == MATE)
	{
		return VALID_MATE;
	}
	setKingPosition(tmpPlaceKing, _turn);
	this->getPiece(indexes[0], indexes[1]) = this->getPiece(indexes[2], indexes[3]);
	this->getPiece(indexes[2], indexes[3]) = copy;
	return VALID_MOVE;
}

bool Board::getTurn() const
{
	return this->_turn;
}

codes Board::move(string indexes)
{
	codes code = this->checkValid(indexes);
	if (code == VALID_MOVE || code == VALID_CHECK_MOVE)
	{
		this->getPiece(indexes[2], indexes[3]) = this->getPiece(indexes[0], indexes[1]);
		this->getPiece(indexes[0], indexes[1]) = nullptr;
		this->changeTurn();
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
	this->_turn = !this->_turn;
}

vector<string> Board::findWay(string indexes)
{
	vector<string> way;
	if (abs((int)(indexes[0] - indexes[2])) == 1 &&
		abs((int)(indexes[1] - indexes[2])) == 1) // pawn move
	{
		way.push_back(indexes.substr(0, 2));
	}
	else if (abs((int)(indexes[0] - indexes[2])) ==
		abs((int)(indexes[1] - indexes[3]))) // bishop move
	{
		for (int i = 0; i < abs((int)(indexes[0] - indexes[2])); i++)
		{
			way.push_back(string(1, (indexes[0] + (indexes[0] > indexes[2] ? -i : i))) +
				string(1, (indexes[1] + (indexes[1] > indexes[3] ? -i : i))));
		}
	}
	else if (!abs((int)(indexes[0] - indexes[2])) && abs((int)(indexes[1] - indexes[3])) ||
		abs((int)(indexes[0] - indexes[2])) && !abs((int)(indexes[1] - indexes[3]))) // rook move
	{
		int difference = abs((int)(indexes[0] - indexes[2])) ?
			abs((int)(indexes[0] - indexes[2])) : abs((int)(indexes[1] - indexes[3]));
		for (int i = 0; i < difference; i++)
		{
			char step = abs((int)(indexes[0] - indexes[2])) ? // horizontal
				(indexes[0] + (indexes[0] > indexes[2] ? -i : i)) :
				(indexes[1] + (indexes[1] > indexes[3] ? -i : i));
			abs((int)(indexes[0] - indexes[2])) ?
				way.push_back(string(1, step) + string(1, indexes[1])) :
				way.push_back(string(1, indexes[0]) + string(1, step));
		}
	}
	else if (abs((int)(indexes[0] - indexes[2])) == 2 && abs((int)(indexes[1] - indexes[3])) == 1 ||
		abs((int)(indexes[0] - indexes[2])) == 1 && abs((int)(indexes[1] - indexes[3])) == 2) // knight
	{
		way.push_back(indexes.substr(0, 2));
	}
	return way;
}

checkMate Board::isCheckMate(bool turn)
{
	bool tmpTurn = this->_turn;
	for (char i = 'a'; i <= 'h'; i++)
	{
		for (char j = '1'; j <= '8'; j++)
		{
			this->changeTurn();
			if (this->checkValid(string(1, i) + string(1, j) +
				(turn == WHITE ? _whiteKing : _blackKing)) == VALID_MOVE)
			{
				vector<string> way = this->findWay(string(1, i) + string(1, j) +
					(turn == WHITE ? _whiteKing : _blackKing));
				this->_turn = !this->_turn;
				if (isMate(way, turn))
				{
					return MATE;
				}
				this->_turn = tmpTurn;
				return CHECK;
			}
		}
	}
	this->_turn = tmpTurn;
	return NOTHING;
}

bool Board::isMate(vector<string> way, bool turn)
{
	string kingPos = (turn == WHITE ? this->_whiteKing : this->_blackKing);
	for (int i = -1; i < 2; i++) // first check -> if the king can move
	{
		for (int j = -1; j < 2; j++)
		{
			if (i == 1 && j == -1)
			{
				cout << "hi";
			}
			if (this->checkValid(kingPos + string(1, (kingPos[0] + i)) + string(1, (kingPos[1] + j))) == VALID_MOVE)
			{
				return false;
			}
		}
	}
	for (size_t i = 0; i < way.size(); i++) // second check -> if another piece can capture / protect it
	{
		for (char j = 'a'; j <= 'h'; j++)
		{
			for (char k = '1'; k <= '8'; k++)
			{
				if (this->checkValid(string(1, j) + string(1, k) + way[i]) == VALID_MOVE)
				{
					return false;
				}
			}
		}
	}
	return true;
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