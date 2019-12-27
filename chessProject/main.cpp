#include <iostream>
#include "Pipe.h"
#include "Board.h"

using std::string;

int main()
{
	system("Start chessGraphics.exe");
	Sleep(1000);

	Pipe p;
	p.connect();
	p.sendMessageToGraphics("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");
	cout << p.getMessageFromGraphics();
	p.sendMessageToGraphics("0");
	cout << p.getMessageFromGraphics();
	p.sendMessageToGraphics("rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR0");

	/*Board b;
	string messageFromGraphics, messageToGraphics;
	while ((messageFromGraphics = b.getMessageFromGraphics()) != "quit")
	{
		messageToGraphics = std::to_string(b.move(messageFromGraphics));
		b.sendMessageToGraphics(messageToGraphics);
	}*/

	return 0;
}