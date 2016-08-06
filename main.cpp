#include "Board.h"
#include "Figure.h"
#include "Interface.h"
#include "Computer.h"
#include "Game.h"

#ifndef _WIN32
system("clear");
#endif

using namespace std;

int main(int argc, char* argv[]) {

	Game game;
	Interface inter;
	Board board(true, false);//Pierwsza zmienna(opcja gry z komputerem: player = false; computerPlayer = true) druga zmienna: gra dla dwoch graczy: (false - gra dla dwoch graczy, true - gra z komputerem).
	Computer computer(false);
	Connector c;

	bool player = true;				// du¿e pionki
	string startPosition;
	string endPosition;
	string command;
	string msg_Command;
	char exit = 'n';
	int playerNr;
	bool moveCorrectness = true;

	game.gameStart(inter, board, computer);

	if (inter.getTerminalMode()) {
		srand((unsigned) time(NULL));

		if ((argc == 2) && (strstr(argv[1], "reset") != NULL)) {// if the last run of the program ends with any error then call the program with the reset parameter
			c.reset();
			return 0;
		}
		cout << "connecting..." << endl;
		playerNr = game.connect(c);
		if (playerNr == 1) {
			player = true;
		} else if (playerNr == 2) {
			player = false;
		} else {
			cout << "Player error...";
		}

		game.wait(3);
		cout << "Let's start!";
		game.wait(3);
		inter.clearScreen();

		inter.draw(board);
		inter.menu();
	}

	do {
		if (inter.getTerminalMode() && playerNr == 2) {

			for (int i = 0; i <= 5; i++) {
				inter.clearLine(17 + i);
			}

			inter.gotoXY(0, 17);
			cout << "Czekaj na ruch gracza numer 1" << endl;

			if (moveCorrectness) {
				string msg;
				c.receive(msg);

				inter.clearLine(17);

				string startPosition = "";
				string endPosition = "";

				startPosition.insert(0, msg, 0, 2);
				endPosition.insert(0, msg, 3, 2);
				cout << startPosition << " ; " << endPosition << endl;
				pair<int, int> startPos = board.getPosition(startPosition);
				pair<int, int> endPos = board.getPosition(endPosition);

				bool tempPlayer = !player;

				Figure chessPiece(board.getChessPiece(startPosition),
						tempPlayer);

				if (chessPiece.isYour(endPos, board)) {

					bool chessPieceMoveCorrectness = chessPiece.move(tempPlayer,
							startPos, endPos, board);

					if (chessPieceMoveCorrectness) {

						board.move(startPosition, endPosition, board,
								tempPlayer);
						inter.changeFigurePosition(board);

						game.checkAndCheckMateVerification(chessPiece,
								tempPlayer, board, inter, exit);
					}
				}
				inter.draw(board);
			}

		}

		game.whoseMoveInformation(msg_Command, board, inter, player);

		if (!computer.getPlayWithComputer() || player) // warunek do grania  1v1 || warunek do grania 1vsCPU
				{

			game.menuCommands(command, inter, exit);
			moveCorrectness = board.checkMove(command, board);

			if (moveCorrectness) {

				if (board.checkFigure(startPosition, endPosition, command,
						board, player, exit)) {

					game.playerMove(startPosition, endPosition, command, board,
							player, inter, exit);
					if (inter.getTerminalMode()) {
						string commandMove = startPosition + " " + endPosition;
						game.terminalGame(playerNr, c, commandMove, inter,
								board, player, exit);
						player = !player;
					}
				} else {
					moveCorrectness = false;
				}
			} else {

				game.wrongCommand(inter, board);

			}

			game.pressEnterToContinue(inter);
		}

		if (computer.getPlayWithComputer() && !player) //ruch komputera
				{

			game.computerMove(computer, startPosition, endPosition, command,
					board, player, inter, exit);
		}

	} while (exit != 't');

}
