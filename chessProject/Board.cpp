#include "Board.h"

Board::Board()
{
	this->_turn = WHITE;
	string boardStr = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0";
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
				break;
			}
		}
	}
	if (!_p.connect())
	{
		cout << "Can't connect to the game!\n";
	}
	this->_p.sendMessageToGraphics(boardStr.c_str());
}

void Board::printBoard()
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (this->_board[i][j] == nullptr)
			{
				cout << "- ";
			}
			else
			{
				cout << "x ";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}

string Board::getMessageFromGraphics()
{
	return this->_p.getMessageFromGraphics();
}

void Board::sendMessageToGraphics(string msg)
{
	this->_p.sendMessageToGraphics(msg.c_str());
}

void Board::setKingPosition(string pos, color color)
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

bool Board::getTurn() const
{
	return this->_turn;
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

codes Board::move(string indexes)
{
	codes code = this->checkValid(indexes);
	if (code == CASTLING_MOVE)
	{
		code = this->castling(indexes);
	}
	if (code != VALID_MOVE)
	{
		return code;
	}
	this->getPiece(indexes[2], indexes[3]) = this->getPiece(indexes[0], indexes[1]);
	this->getPiece(indexes[0], indexes[1]) = nullptr;
	if (this->isCheck(this->_turn == WHITE ? BLACK : WHITE)) // check on the other player
	{
		if (isMate(this->_turn))
		{
			return VALID_MATE;
		}
		this->changeTurn();
		return VALID_CHECK_MOVE;
	}
	this->changeTurn();
	printBoard();
	return code;
}

codes Board::checkBasicValid(string indexes)
{
	if (indexes[0] > 'h' || indexes[0] < 'a' || indexes[1] > '8' || indexes[1] < '1' ||
		indexes[2] > 'h' || indexes[2] < 'a' || indexes[3] > '8' || indexes[3] < '1') // we need this for the king move,
		// we did in the function isMate invalid moves..
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

	return this->getPiece(indexes[0], indexes[1])->checkValid(indexes);
}

codes Board::checkValid(string indexes)
{
	codes code = checkBasicValid(indexes);
	if (code != VALID_MOVE)
	{
		return code;
	}
	string tmpKingPos = this->getPiece(indexes[0], indexes[1])->getColor() == WHITE ? this->_whiteKing : this->_blackKing;
	code = this->getPiece(indexes[0], indexes[1])->checkValid(indexes);
	Piece* copy;
	if (code == VALID_MOVE) // then move the piece
	{
		copy = this->getPiece(indexes[2], indexes[3]);
		this->getPiece(indexes[2], indexes[3]) = this->getPiece(indexes[0], indexes[1]);
		this->getPiece(indexes[0], indexes[1]) = nullptr;
	}
	else
	{
		return code;
	}
	if (this->isCheck(this->_turn)) // check on the current player
	{
		this->getPiece(indexes[0], indexes[1]) = this->getPiece(indexes[2], indexes[3]);
		this->getPiece(indexes[2], indexes[3]) = copy;
		this->setKingPosition(tmpKingPos, this->getPiece(indexes[0], indexes[1])->getColor());
		return INVALID_SELF_CHECK_MOVE;
	}
	this->getPiece(indexes[0], indexes[1]) = this->getPiece(indexes[2], indexes[3]);
	this->getPiece(indexes[2], indexes[3]) = copy;
	return VALID_MOVE;
}

bool Board::isCheck(color turn)
{
	color tmpTurn = this->_turn;
	this->_turn = turn == WHITE ? BLACK : WHITE;
	for (char i = 'a'; i <= 'h'; i++)
	{
		for (char j = '1'; j <= '8'; j++)
		{
			if (this->checkBasicValid(string(1, i) + string(1, j) +
				(turn == WHITE ? _whiteKing : _blackKing)) == VALID_MOVE)
			{
				this->_turn = tmpTurn;
				return true;
			}
		}
	}
	this->_turn = tmpTurn;
	return false;
}

bool Board::isMate(color turn)
{
	color tmpTurn = this->_turn;
	this->_turn = turn == WHITE ? BLACK : WHITE;
	string kingPos = (turn == WHITE ? this->_whiteKing : this->_blackKing);
	for (char i = 'a'; i <= 'h'; i++)
	{
		for (char j = '1'; j <= '8'; j++)
		{
			for (char k = 'a'; k <= 'h'; k++)
			{
				for (char l = '1'; l <= '8'; l++)
				{
					if (this->getPiece(i, j) != nullptr && this->getPiece(i, j)->getColor() != turn)
					{
						if (this->checkValid(string(1, i) + string(1, j) + string(1, k) + string(1, l)) == VALID_MOVE)
						{
							this->_turn = tmpTurn;
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

codes Board::castling(string indexes)
{
	if (!(indexes == "e1g1" && this->_turn == WHITE && this->checkValid("h1f1") == VALID_MOVE ||
	indexes == "e1c1" && this->_turn == WHITE && this->checkValid("a1d1") == VALID_MOVE ||
	indexes == "e8g8" && this->_turn == BLACK && this->checkValid("h8f8") == VALID_MOVE ||
	indexes == "e8c8" && this->_turn == BLACK && this->checkValid("a8d8") == VALID_MOVE))
	{
		return INVALID_PIECE_MOVE;
	}
	for (int i = 1; i < abs((int)(indexes[1]-indexes[3])); i++)
	{
		if (this->getPiece(indexes[0] + (indexes[0] > indexes[2] ? -i : i), indexes[1]) != nullptr)
		{
			return INVALID_PIECE_MOVE;
		}
	}
	this->getPiece(indexes[2], indexes[3]) = this->getPiece(indexes[0], indexes[1]);
	this->getPiece(indexes[0], indexes[1]) = nullptr;
	if (indexes[0] > indexes[2])
	{
		this->getPiece('d', indexes[1]) = this->getPiece('a', indexes[1]);
		this->getPiece('a', indexes[1]) = nullptr;
	}
	else
	{
		this->getPiece('f', indexes[1]) = this->getPiece('h', indexes[1]);
		this->getPiece('h', indexes[1]) = nullptr;
	}
	this->_p.close();
	system("taskkill /IM ChessGraphics.exe");
	system("Start ChessGraphics.exe");
	Sleep(1000);
	if (!_p.connect())
	{
		cout << "Can't connect to the game!\n";
	}
	this->_p.sendMessageToGraphics(this->makeBoardStr(this->_turn == WHITE ? BLACK : WHITE).c_str());
	this->_p.getMessageFromGraphics();
	return VALID_MOVE;
}

string Board::makeBoardStr(color turn)
{
	string boardStr = "";
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (this->_board[i][j] == nullptr)
			{
				boardStr += '#';
			}
			else
			{
				boardStr += _board[i][j]->getColor() == WHITE ?
					_board[i][j]->getType() : tolower(_board[i][j]->getType());
			}
		}
	}
	boardStr += turn == WHITE ? '0' : '1';
	return boardStr;
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
