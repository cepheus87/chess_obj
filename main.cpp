#include "Board.h"
#include "Figure.h"
#include "Interface.h"
#include "Computer.h"

using namespace std;

int main(int argc, char* argv[])
{

	#ifndef _WIN32
		system("clear");
	#endif

	Interface inter;
	Board board(true, false);		//Pierwsza zmienna(opcja gry z komputerem: player = false; computerPlayer = true) druga zmienna: gra dla dwoch graczy: (false - gra dla dwoch graczy, true - gra z komputerem).
	Computer computer(false);
	bool player = true;				// du¿e pionki

	inter.gameType(board, computer);
	inter.draw(board);
	inter.menu();     //wypisanie instrukcji

	string startPosition;
	string endPosition;
	string command;
	char exit = 'n';
	std::string msg_Command;

	do
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

		if(!computer.getPlayWithComputer() || player)
			{
			std::getline(std::cin,command);
			std::string modyfiedCommand = inter.checkCommands(command);

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

		if(!computer.getPlayWithComputer() || player) // warunek do grania  1v1 || warunek do grania 1vsCPU
		{
			bool moveCorrectness = board.checkMove(command,board);

			if(moveCorrectness)
			{

					string startPosition = "";
					string endPosition = "";

					startPosition.insert( 0, command, 0, 2 );
					endPosition.insert( 0, command, 2, 2 );

					Figure chessPiece(board.getChessPiece(startPosition),player);

					pair<int,int> startPos = board.getPosition(startPosition);
					pair<int,int> endPos = board.getPosition(endPosition);

					if(chessPiece.isYour(endPos, board) )
						{
							bool chessPieceMoveCorrectness = chessPiece.move(player,startPos, endPos, board);

							if(chessPieceMoveCorrectness){

								board.move(startPosition, endPosition, board, player);   //jesli komenda poprawna - wykonaj ruch
								inter.changeFigurePosition(board);

								//!Sprawdzanie szachu i szach-matu
								std::pair<int,int> checks=chessPiece.isItCheck(!player,board);
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
						}
				}
				else
				{
					//jesli komenda nie poprawna
					inter.gotoXY(0,19);
					if(board.getComputerPlayer())
						cout<<"Ruch nie zostanie wykonany. Podaj jeszcze raz potrzebne pola!"<<endl;
				}
				inter.gotoXY(0,20);
				cout << "Nacisnij ENTER aby kontynulowac...";
				while (getchar() != '\n'){}
		}

		if(computer.getPlayWithComputer() && !player) //ruch komputera
		{
			cout << "Ruch komputera..." << endl;
			while(1)
			{
				string generatedMove = computer.generate(board);

				startPosition.insert( 0, generatedMove, 0, 2 );
				endPosition.insert( 0, generatedMove, 2, 2 );

				Figure chessPiece(board.getChessPiece(startPosition),player);

				pair<int,int> startPos = board.getPosition(startPosition);
				pair<int,int> endPos = board.getPosition(endPosition);

				bool chessPieceMoveCorrectness = chessPiece.move(player,startPos, endPos, board);

				if(chessPieceMoveCorrectness)
					{

					board.move(startPosition, endPosition, board, player);   //jesli komenda poprawna - wykonaj ruch
					inter.changeFigurePosition(board);
					//!Sprawdzanie szachu i szach-matu
					std::pair<int,int> checks=chessPiece.isItCheck(!player,board);
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
			inter.gotoXY(0,20);
			cout << "Nacisnij ENTER aby kontynulowac...";
			//Oczekiwanie na enter
			while (getchar() != '\n'){}
		}
	}
	while(exit != 't');
}
