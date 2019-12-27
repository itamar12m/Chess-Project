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

void Board::printBoard()
{
	for (size_t i = 0; i < 8; i++) // for the debugging
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (this->_board[i][j] == nullptr)
			{
				cout << "- ";
			}
			else
			{
				cout << "o ";
			}
		}
		cout << endl;
	}
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

int Board::move(string indexes)
{
	string tmpPlaceKing = (_turn == WHITE ? _whiteKing : _blackKing);
	int code = this->checkValid(indexes);
	Piece* copy = nullptr;
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
		setKingPosition(tmpPlaceKing, _turn);
		this->getPiece(indexes[0], indexes[1]) = this->getPiece(indexes[2], indexes[3]);
		this->getPiece(indexes[2], indexes[3]) = copy;
		code = INVALID_SELF_CHECK_MOVE;
	}
	else if (this->isCheckMate(!this->_turn) == CHECK) // check on the other player
	{
		code = VALID_CHECK_MOVE;
	}
	else if (this->isCheckMate(!this->_turn) == MATE)
	{
		return VALID_MATE;
	}
	if (code == VALID_CHECK_MOVE || code == VALID_MOVE)
	{
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
	bool bishopMove = abs((int)(indexes[0] - indexes[2])) == abs((int)(indexes[1] - indexes[3]));
	bool rookMove = !abs((int)(indexes[0] - indexes[2])) && abs((int)(indexes[1] - indexes[3])) ||
		abs((int)(indexes[0] - indexes[2])) && !abs((int)(indexes[1] - indexes[3]));
	bool pawnMove = abs((int)(indexes[0] - indexes[2])) == 1 && abs((int)(indexes[1] - indexes[2])) == 1;
	if (pawnMove)
	{
		way.push_back(indexes.substr(0, 2));
	}
	else if (bishopMove)
	{
		for (int i = 0; i < abs((int)(indexes[0] - indexes[2])); i++)
		{
			way.push_back(string(1, (indexes[0] + (indexes[0] > indexes[2] ? -i : i))) +
				string(1, (indexes[1] + (indexes[1] > indexes[3] ? -i : i))));
		}
	}
	else if (rookMove)
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
	return way;
}

checkMate Board::isCheckMate(bool turn)
{
	bool tmpTurn = this->_turn;
	for (char i = 'a'; i <= 'h'; i++)
	{
		for (char j = '1'; j <= '8'; j++)
		{
			this->_turn = !turn;
			if (this->checkValid(string(1, i) + string(1, j) +
				(turn == WHITE ? _whiteKing : _blackKing)) == VALID_MOVE)
			{
				vector<string> way = this->findWay(string(1, i) + string(1, j) +
					(turn == WHITE ? _whiteKing : _blackKing));
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
	for (char i = 0; i < 2; i++) // first check -> if the king can move
	{
		for (char j = 0; j < 2; j++)
		{
			if (this->move(kingPos + string(1, (kingPos[0] + i)) + string(1, (kingPos[1] + j))) == VALID_MOVE)
			{
				return false;
			}
		}
	}
	for (size_t i = 0; i < way.size(); i++) // second check -> if another piece can capture / protect
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