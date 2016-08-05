#include "Board.h"
#include "Figure.h"
#include "Interface.h"
#include "Computer.h"
#include "Game.h"

#ifndef _WIN32
	system("clear");
#endif

using namespace std;

int main(int argc, char* argv[])
{

	Game game;
	Interface inter;
	Board board(true, false);		//Pierwsza zmienna(opcja gry z komputerem: player = false; computerPlayer = true) druga zmienna: gra dla dwoch graczy: (false - gra dla dwoch graczy, true - gra z komputerem).
	Computer computer(false);

	bool player = true;				// du¿e pionki
	string startPosition;
	string endPosition;
	string command;
	string msg_Command;
	char exit = 'n';

	game.gameStart(inter, board, computer, argc, argv);

	do
	{
		game.whoseMoveInformation(msg_Command, board, inter, player);

		if(!computer.getPlayWithComputer() || player) // warunek do grania  1v1 || warunek do grania 1vsCPU
		{
			game.menuCommands(command, inter, exit);
			bool moveCorrectness = board.checkMove(command, board);

			if(moveCorrectness)
			{
				game.playerMove(startPosition, endPosition, command, board, player, inter, exit);
			}

			else
			{
				game.wrongCommand(inter, board);
			}

			game.pressEnterToContinue(inter);
		}

		if(computer.getPlayWithComputer() && !player) //ruch komputera
		{
			game.computerMove(computer, startPosition, endPosition, command, board, player, inter, exit);
		}

	}
	while(exit != 't');

}
