#include "Board.h"
#include "Figure.h"
#include "Interface.h"

using namespace std;

int main(int argc, char* argv[])
{

	#ifndef _WIN32
	system("clear");
	#endif

	Interface inter;
	Board board;

	inter.draw(board);

	bool player = true;				// du¿e pionki

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
				msg_Command = "CZARNY: Prosze podac polecenie lub pole pionka i pole docelowe ruchu: ";
			}

		inter.gotoXY(0,17);
		cout << msg_Command;
		std::getline(std::cin,command);
		std::string modyfiedCommand = inter.checkCommands(command);

		if (modyfiedCommand=="help")
			{
				inter.clearLine(17);
				inter.gotoXY(0,17);
				inter.help();
			}else if (modyfiedCommand=="quit")
				{
				inter.clearLine(17);
				inter.gotoXY(0,17);
				cout <<"Wyjscie z gry"<<endl;
				exit='t';
			}else{

				//Sprawdzanie poprawnosci wpisanej komendy
				bool moveCorrectness = board.checkMove(command,board);

				if(moveCorrectness){


					string startPosition = "";
					string endPosition = "";

					startPosition.insert( 0, command, 0, 2 );
					endPosition.insert( 0, command, 2, 2 );

					Figure chessPiece(board.getChessPiece(startPosition));

					pair<int,int> startPos = board.getPosition(startPosition);
					pair<int,int> endPos = board.getPosition(endPosition);

					if(chessPiece.isYour(endPos, board) )
					{
						bool chessPieceMoveCorrectness = chessPiece.move(startPos, endPos, board);

						if(chessPieceMoveCorrectness){

							board.move(startPosition, endPosition, board, player);   //jesli komenda poprawna - wykonaj ruch
							inter.changeFigurePosition(board);
						}
					}

				} else {
				//jesli komenda nie poprawna
				inter.gotoXY(0,19);
				cout<<"Ruch nie zostanie wykonany. Podaj jeszcze raz potrzebne pola!"<<endl;
				}

				inter.gotoXY(0,20);
				cout << "Nacisnij ENTER aby kontynulowac...";

				//Oczekiwanie na enter
				while (getchar() != '\n'){}
			}
	}while(exit != 't');


}
