#include "Pipe.h"
#include <iostream>
#include "Board.h"

using std::string;

int main()
{
	system("Start chessGraphics.exe");
	Sleep(1000);

	Board b;
	string messageFromGraphics, messageToGraphics;
	while ((messageFromGraphics = b.getMessageFromGraphics()) != "quit")
	{
		messageToGraphics = std::to_string(b.move(messageFromGraphics));
		b.sendMessageToGraphics(messageToGraphics);
	}

	return 0;
}