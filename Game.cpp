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

int Game::connect(Connector& c)
{
	int retVal;
    cout << "Connecting, please wait..." << endl;
    if ((retVal = c.connect()) == 1) {
        cout << "I am player 1, waiting for player 2 to connect..." << endl;
        if (c.waitForConnection()) {
            cout << "Player 2 connected!" << endl;
			return 1;
        } else
            cout << "Player 2 did not connect during the specified timeout!" << endl;
    } else {
        cout << "I am player 2" << endl;
	}
	return retVal;
}



int Game::terminalGame(int argc, char *argv[])
{
	srand((unsigned)time(NULL));

	    Connector c;
		if ((argc == 2) && (strstr(argv[1], "reset") != NULL)) {	// if the last run of the program ends with any error then call the program with the reset parameter
			c.reset();
			return 0;
		}
	    cout << "connecting..." << endl;
	    int playerNr = connect(c);
		int i = 0;
		do {
			if (playerNr == 1){
//				player1(c);
			}
			else if (playerNr == 2){
//				player2(c);
			}
			if (c.errCode != CONNECTOR_NO_ERROR)
			{
				cout << "error, errCode = " << hex << c.errCode << endl;
				return 1;
			}
			wait(3);
			i++;
		} while (i < 5);

		cout << "disconnecting..." << endl;
		c.disconnect();

		if (c.errCode != CONNECTOR_NO_ERROR)
		{
			cout << "error while disconnecting, errCode = " << hex << c.errCode << endl;
			return 1;
		}
}

void Game::gameStart(Interface& inter, Board& board, Computer& computer, int argc, char *argv[] )
{

	inter.gameType(board, computer);

	if(inter.getTerminalMode())
	{
		terminalGame(argc, argv);
	}

	inter.draw(board);



	inter.menu();     //wypisanie instrukcji
}

void Game::whoseMoveInformation(string& msg_Command, Board& board, Interface& inter, bool& player )
{
	for (int i=0; i<=5;i++)
	{
		inter.clearLine(17+i);
	}

	if (player)
		{
			msg_Command = "BIALY: Prosze podac polecenie lub pole pionka i pole docelowe ruchu: ";
		}
		else
		{
			if( board.getComputerPlayer() || board.getTwoPlayers() ){
				msg_Command = "CZARNY: Prosze podac polecenie lub pole pionka i pole docelowe ruchu: ";
			}else{
				msg_Command = "KOMPUTER: Czekaj... ";
			}
		}

	inter.gotoXY(0,17);
	cout << msg_Command;
}

void Game::menuCommands(string& command, Interface& inter, char& exit)
{

	getline(cin,command);
	string modyfiedCommand = inter.checkCommands(command);

	if (modyfiedCommand=="help")
	{
		inter.clearLine(17);
		inter.gotoXY(0,17);
		inter.help();
	}

	if (modyfiedCommand=="quit")
	{
		inter.clearLine(17);
		inter.gotoXY(0,17);
		cout <<"Wyjscie z gry"<<endl;
		exit='t';
	}
}

void Game::checkAndCheckMateVerification(Figure& chessPiece, bool& player, Board& board, Interface& inter, char& exit)
{
	pair<int,int> checks=chessPiece.isItCheck(!player,board);
	if(checks.first!=100) //jesli jest szach
	{
		if(chessPiece.isItCheckMate(!player,checks,board))
	    {//Jest szach mat
			inter.clearLine(19);
			inter.clearLine(18);
	        if(!player)
	        {
	         cout<<"SZACH MAT dla gracza bialego"<<endl;
	         cout<<"Brawo! Wygral gracz bialy!"<<endl;
	        }
	        else
	        {
	        cout <<"SZACH MAT dla gracza czarnego"<<endl;
	        cout<<"Brawo! Wygral gracz czarny!"<<endl;
	         }
	          exit='t';
	     }
		 else
		 {//Jest tylko szach
			 inter.clearLine(18);
			 if(!player)
			 {
				 cout<<"SZACH dla gracza bialego"<<endl;
			 }
			 else
			 {
				 cout <<"SZACH dla gracza czarnego"<<endl;
			 }
		 }
	}
}

void Game::wrongCommand(Interface& inter, Board& board)
{
	inter.gotoXY(0,19);
	if(board.getComputerPlayer())
	cout<<"Ruch nie zostanie wykonany. Podaj jeszcze raz potrzebne pola!"<<endl;
}

void Game::pressEnterToContinue(Interface& inter)
{
	inter.gotoXY(0,20);
	cout << "Nacisnij ENTER aby kontynulowac...";
	while (getchar() != '\n'){}
}

void Game::playerMove(string& startPosition, string& endPosition, string& command, Board& board, bool& player, Interface& inter, char& exit)
{
	startPosition = "";
	endPosition = "";

	startPosition.insert( 0, command, 0, 2 );
	endPosition.insert( 0, command, 2, 2 );

	pair<int,int> startPos = board.getPosition(startPosition);
	pair<int,int> endPos = board.getPosition(endPosition);

	Figure chessPiece(board.getChessPiece(startPosition),player);

	if(chessPiece.isYour(endPos, board) )
		{
			bool chessPieceMoveCorrectness = chessPiece.move(player,startPos, endPos, board);

			if(chessPieceMoveCorrectness){

				board.move(startPosition, endPosition, board, player);
				inter.changeFigurePosition(board);

				checkAndCheckMateVerification(chessPiece, player, board, inter, exit);
			}
		}
}

void Game::computerMove(Computer& computer, string& startPosition, string& endPosition, string& command, Board& board, bool& player, Interface& inter, char& exit)
{
	cout << "Ruch komputera..." << endl;
	while(1)
	{
		string generatedMove = computer.generate(board);

		startPosition.insert( 0, generatedMove, 0, 2 );
		endPosition.insert( 0, generatedMove, 2, 2 );

		pair<int,int> startPos = board.getPosition(startPosition);
		pair<int,int> endPos = board.getPosition(endPosition);

		Figure chessPiece(board.getChessPiece(startPosition),player);

		bool chessPieceMoveCorrectness = chessPiece.move(player,startPos, endPos, board);

		if(chessPieceMoveCorrectness)
			{

			board.move(startPosition, endPosition, board, player);
			inter.changeFigurePosition(board);

			checkAndCheckMateVerification(chessPiece, player, board, inter, exit);
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


