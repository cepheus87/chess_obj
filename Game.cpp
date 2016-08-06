/*
 * Game.cpp
 *
 *  Created on: 05.08.2016
 *      Author: qbba7
 */

#include "Game.h"

Game::Game() {
	// TODO Auto-generated constructor stub
}

int Game::connect(Connector& c) {
	int retVal;
	cout << "Connecting, please wait..." << endl;
	if ((retVal = c.connect()) == 1) {
		cout << "I am player 1, waiting for player 2 to connect..." << endl;
		if (c.waitForConnection()) {
			cout << "Player 2 connected!" << endl;
			return 1;
		} else
			cout << "Player 2 did not connect during the specified timeout!"
					<< endl;
	} else {
		cout << "I am player 2" << endl;
	}
	return retVal;
}

bool Game::player1(Connector& c, string commandMove, Interface& inter,
		Board& board, bool player, char& exit) {

	string move = commandMove;
	cout << "Sending my move to player 2: " << move << endl;
	c.send(move);

	string msg;
	cout << "Waiting for response from player 2..." << endl;
	c.receive(msg);

	cout << "Player 2 sent: " << msg << endl;

	string startPosition = "";
	string endPosition = "";

	startPosition.insert(0, msg, 0, 2);
	endPosition.insert(0, msg, 3, 2);

	pair<int, int> startPos = board.getPosition(startPosition);
	pair<int, int> endPos = board.getPosition(endPosition);

	bool tempPlayer = player;

	Figure chessPiece(board.getChessPiece(startPosition), tempPlayer);

	if (chessPiece.isYour(endPos, board)) {
		bool chessPieceMoveCorrectness = chessPiece.move(tempPlayer, startPos,
				endPos, board);

		if (chessPieceMoveCorrectness) {

			board.move(startPosition, endPosition, board, tempPlayer);
			inter.changeFigurePosition(board);

			checkAndCheckMateVerification(chessPiece, tempPlayer, board, inter,
					exit);
		}
	}

	return (c.errCode == CONNECTOR_NO_ERROR);
}

bool Game::player2(Connector& c, string commandMove, Interface& inter,
		Board& board, bool player, char& exit) {

	inter.gotoXY(0, 19);

	string move = commandMove;
	cout << "Sending my move to player 1:  " << move << endl;
	c.send(move);

	return (c.errCode == CONNECTOR_NO_ERROR);
}

int Game::terminalGame(int playerNr, Connector& c, string commandMove,
		Interface& inter, Board& board, bool player, char& exit) {
	for (int i = 0; i <= 5; i++) {
		inter.clearLine(19 + i);
	}

	inter.gotoXY(0, 19);
	int i = 0;
	//do {
	if (playerNr == 1) {
		player1(c, commandMove, inter, board, player, exit);
	} else if (playerNr == 2) {
		player2(c, commandMove, inter, board, player, exit);
	}
	if (c.errCode != CONNECTOR_NO_ERROR) {
		cout << "error, errCode = " << hex << c.errCode << endl;
		return 1;
	}
	wait(3);
	i++;
	//} while (i < 1);
	/*
	 cout << "disconnecting..." << endl;
	 c.disconnect();

	 if (c.errCode != CONNECTOR_NO_ERROR)
	 {
	 cout << "error while disconnecting, errCode = " << hex << c.errCode << endl;
	 return 1;
	 }*/
}

void Game::gameStart(Interface& inter, Board& board, Computer& computer) {

	inter.gameType(board, computer);

	if (!inter.getTerminalMode()) {
		inter.draw(board);
		inter.menu();     //wypisanie instrukcji
	}
}

void Game::whoseMoveInformation(string& msg_Command, Board& board,
		Interface& inter, bool& player) {
	for (int i = 0; i <= 5; i++) {
		inter.clearLine(17 + i);
	}

	if (player) {
		msg_Command =
				"BIALY: Prosze podac polecenie lub pole pionka i pole docelowe ruchu: ";
	} else {
		if (board.getComputerPlayer() || board.getTwoPlayers()) {
			msg_Command =
					"CZARNY: Prosze podac polecenie lub pole pionka i pole docelowe ruchu: ";
		} else {
			msg_Command = "KOMPUTER: Czekaj... ";
		}
	}

	inter.gotoXY(0, 17);
	cout << msg_Command;
}

void Game::menuCommands(string& command, Interface& inter, char& exit) {

	getline(cin, command);
	string modyfiedCommand = inter.checkCommands(command);

	if (modyfiedCommand == "help") {
		inter.clearLine(17);
		inter.gotoXY(0, 17);
		inter.help();
	}

	if (modyfiedCommand == "quit") {
		inter.clearLine(17);
		inter.gotoXY(0, 17);
		cout << "Wyjscie z gry" << endl;
		exit = 't';
	}
}

void Game::checkAndCheckMateVerification(Figure& chessPiece, bool& player,
		Board& board, Interface& inter, char& exit) {
	pair<int, int> checks = chessPiece.isItCheck(!player, board);
	if (checks.first != 100) //jesli jest szach
			{
		if (chessPiece.isItCheckMate(!player, checks, board)) { //Jest szach mat
			inter.clearLine(19);
			inter.clearLine(18);
			if (!player) {
				cout << "SZACH MAT dla gracza bialego" << endl;
				cout << "Brawo! Wygral gracz bialy!" << endl;
			} else {
				cout << "SZACH MAT dla gracza czarnego" << endl;
				cout << "Brawo! Wygral gracz czarny!" << endl;
			}
			exit = 't';
		} else { //Jest tylko szach
			inter.clearLine(18);
			if (!player) {
				cout << "SZACH dla gracza bialego" << endl;
			} else {
				cout << "SZACH dla gracza czarnego" << endl;
			}
		}
	}
}

void Game::wrongCommand(Interface& inter, Board& board) {
	inter.gotoXY(0, 19);
	if (board.getComputerPlayer())
		cout << "Ruch nie zostanie wykonany. Podaj jeszcze raz potrzebne pola!"
				<< endl;
}

void Game::pressEnterToContinue(Interface& inter) {
	inter.gotoXY(0, 22);
	cout << "Nacisnij ENTER aby kontynulowac...";
	while (getchar() != '\n') {
	}
}

void Game::playerMove(string& startPosition, string& endPosition,
		string& command, Board& board, bool& player, Interface& inter,
		char& exit) {
	Figure chessPiece(board.getChessPiece(startPosition), player);
	board.move(startPosition, endPosition, board, player);
	inter.changeFigurePosition(board);
	checkAndCheckMateVerification(chessPiece, player, board, inter, exit);
}

void Game::computerMove(Computer& computer, string& startPosition,
		string& endPosition, string& command, Board& board, bool& player,
		Interface& inter, char& exit) {
	cout << "Ruch komputera..." << endl;
	while (1) {
		string generatedMove = computer.generate(board);

		startPosition.insert(0, generatedMove, 0, 2);
		endPosition.insert(0, generatedMove, 2, 2);

		pair<int, int> startPos = board.getPosition(startPosition);
		pair<int, int> endPos = board.getPosition(endPosition);

		Figure chessPiece(board.getChessPiece(startPosition), player);

		bool chessPieceMoveCorrectness = chessPiece.move(player, startPos,
				endPos, board);

		if (chessPieceMoveCorrectness) {

			board.move(startPosition, endPosition, board, player);
			inter.changeFigurePosition(board);

			checkAndCheckMateVerification(chessPiece, player, board, inter,
					exit);
			break;
		}

		generatedMove = "";
		startPosition = "";
		endPosition = "";
		startPos.first = 0;
		startPos.second = 0;
		endPos.first = 0;
		endPos.second = 0;
	}
	pressEnterToContinue(inter);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

