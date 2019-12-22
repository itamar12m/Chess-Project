#include "Pipe.h"
#include <iostream>
#include "Board.h"

using std::string;

int main()
{
	system("Start chessGraphics.exe");
	Sleep(1000);

	Board b("###k####q###########B##########Q######b###########r######R##K###0");
	string messageFromGraphics, messageToGraphics;
	while ((messageFromGraphics = b.getMessageFromGraphics()) != "quit")
	{
		messageToGraphics = std::to_string(b.move(messageFromGraphics));
		b.sendMessageToGraphics(messageToGraphics);
		if (messageToGraphics == std::to_string(VALID_CHECK_MOVE) ||
			messageToGraphics == std::to_string(VALID_MOVE)) // if it's mate so the game is over..
		{
			b.changeTurn();
		}
	}

	return 0;
}