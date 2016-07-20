#include "Board.h"
#include "Figure.h"
#include "Interface.h"

using namespace std;

int main(int argc, char* argv[])
{
	Board *board = new Board;
	Interface *inter = new Interface;

	#ifndef _WIN32
		system("clear");
	#endif

	bool player = true;				// du¿e pionki

	inter->menu();     //wypisanie instrukcji

	char* b = new char[BOARD_SIZE * BOARD_SIZE];

	board->init((char(*)[BOARD_SIZE])b);
	inter->draw((char(*)[BOARD_SIZE])b);

	string command;
	char exit = 'n';
	std::string msg_Command;

	do
	{
		for (int i=0; i<=5;i++)
		{
			inter->clearLine(17+i);
		}

		if (player)
			{
				msg_Command = "BIALY: Prosze podac polecenie lub pole pionka i pole docelowe ruchu: ";
			}
			else
			{
				msg_Command = "CZARNY: Prosze podac polecenie lub pole pionka i pole docelowe ruchu: ";
			}

		inter->gotoXY(0,17);
		cout<<msg_Command;
		std::getline(std::cin,command);
		std::string modyfiedCommand = inter->checkCommands(command);

		if (modyfiedCommand=="help")
			{
				inter->clearLine(17);
				inter->gotoXY(0,17);
				inter->help();
			}else if (modyfiedCommand=="quit")
				{
				inter -> clearLine(17);
				inter -> gotoXY(0,17);
				cout <<"Wyjscie z gry"<<endl;
				exit='t';
			} else {

				//Sprawdzanie poprawnosci wpisanej komendy
				bool moveCorrectness = (board->checkMove(command,(char(*)[BOARD_SIZE])b));

				if(moveCorrectness){

					string startPosition = "";
					string endPosition = "";

					startPosition.insert( 0, command, 0, 2 );
					endPosition.insert( 0, command, 2, 2 );

					cout << "startPosioin: " << startPosition << endl;
					cout << "endPosition: " << endPosition <<endl;
					//inter->move(startPosition, endPosition, (char(*)[BOARD_SIZE])b,player);   //jesli komenda poprawna - wykonaj ruch

				//moveEngine(getPosition(startPosition), getPosition(endPosition), (char(*)[BOARD_SIZE])b );
				//Na razie zakomentowane - trzeba dopisac
				} else {
				//jesli komenda nie poprawna
				inter -> gotoXY(0,19);
				cout<<"Ruch nie zostanie wykonany. Podaj jeszcze raz potrzebne pola!"<<endl;
				}

				inter -> gotoXY(0,20);
				cout << "Nacisnij ENTER aby kontynulowac...";

				//Oczekiwanie na enter
				while (getchar() != '\n'){}
			}
	}while(exit != 't');

}
