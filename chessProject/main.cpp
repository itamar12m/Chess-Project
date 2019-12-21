/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include "Board.h"

using std::cout;
using std::endl;
using std::string;


int main()
{
	system("Start chessGraphics.exe");
	Sleep(1000);

	Board b("##################################################r#############0");
	string messageFromGraphics, messageToGraphics;
	while ((messageFromGraphics = b.getMessageFromGraphics()) != "quit")
	{
		cout << messageFromGraphics << endl;
		messageToGraphics = std::to_string(b.move(messageFromGraphics));
		b.sendMessageToGraphics(messageToGraphics);
	}

	return 0;
}