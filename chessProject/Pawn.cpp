#include "Pawn.h"

bool Pawn::checkFirst(string indexes)
{
	if (indexes[1] == '7' && _color == BLACK || (indexes[1] == '2' && _color == WHITE))
	{
		return true;
	}
	return false;
}

bool Pawn::isCapture(string indexes)
{
	if (_board->getPiece(indexes[2], indexes[3]) != nullptr &&
		abs((int)(indexes[0] - indexes[2])) == 1 &&
		abs((int)(indexes[1] - indexes[3])) == 1 &&
		(_board->getPiece(indexes[0], indexes[1])->getColor() == WHITE && indexes[3] - indexes[1] == 1 ||
			_board->getPiece(indexes[0], indexes[1])->getColor() == BLACK && indexes[3] - indexes[1] == -1))
	{
		return true;
	}
	return false;
}

int Pawn::checkWayForPawn(string indexes)
{
	if (_board->getPiece(indexes[2], indexes[3]) != nullptr ||
		(_color == BLACK && _board->getPiece(indexes[2], indexes[3] + 1) != nullptr && indexes[3] + 1 != indexes[1] ||
		(_color == WHITE && _board->getPiece(indexes[2], indexes[3] - 1) != nullptr && indexes[3] - 1 != indexes[1])))
	{
		return false;
	}
	return true;
}

void Pawn::promotion(string indexes)
{
	char choose;
	delete _board->getPiece(indexes[2], indexes[3]);
	cout << "What do you want to replace the pawn with?" << endl <<
		"(q - queen, r - rook, b - bishop, n - knight)" << endl;
	cin >> choose;
	switch (choose)
	{
	case 'r':
		_board->getPiece(indexes[2], indexes[3]) = new Rook(_color, _board);
		break;
	case 'n':
		_board->getPiece(indexes[2], indexes[3]) = new Knight(_color, _board);
		break;
	case 'b':
		_board->getPiece(indexes[2], indexes[3]) = new Bishop(_color, _board);
		break;
	case 'q':
		_board->getPiece(indexes[2], indexes[3]) = new Queen(_color, _board);
		break;
	default:
		break;
	}

}

Pawn::Pawn(color color, Board* board) : Piece(color, board)
{
	this->_type = 'P';
}

codes Pawn::checkValid(string indexes)
{
	codes flag = INVALID_PIECE_MOVE;
	if (checkFirst(indexes))
	{
		if (_color == BLACK && (indexes[3] + 2 == indexes[1] || indexes[3] + 1 == indexes[1]) && indexes[0] == indexes[2] && checkWayForPawn(indexes)) {
			return VALID_MOVE;
		}
		if (_color == WHITE && (indexes[3] - 2 == indexes[1] || indexes[3] - 1 == indexes[1]) && indexes[0] == indexes[2] && checkWayForPawn(indexes))
		{
			return VALID_MOVE;
		}
	}
	else if (isCapture(indexes))
	{
		flag = VALID_MOVE;
	}
	else if (((_color == BLACK && indexes[3] + 1 == indexes[1] && indexes[0] == indexes[2]) ||
		(_color == WHITE && indexes[3] - 1 == indexes[1] && indexes[0] == indexes[2])) && checkWayForPawn(indexes))
	{
		flag = VALID_MOVE;
	}
	else
	{
		return INVALID_PIECE_MOVE;
	}/*
	if ((flag == VALID_MOVE || flag == VALID_CHECK_MOVE) &&
		((_color == WHITE && indexes[3] == '8') || (_color == BLACK && indexes[3] == '1')))
	{
		promotion(indexes);
	}*/
	return flag;
}
