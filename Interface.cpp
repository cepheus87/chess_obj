/*
 * Interface.cpp
 *
 *  Created on: 19 lip 2016
 *      Author: Micha³
 */

#include "Interface.h"

Interface::Interface() {
	// TODO Auto-generated constructor stub

}

#ifdef _WIN32

#define MOVE_X_LINUX_CORRECTION 0

	void Interface::gotoXY(short x, short y) const
	{
		COORD coord = {x, y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

#else

#define MOVE_X_LINUX_CORRECTION 1

	void Interface::gotoXY(short x, short y) const
	{
		cout << "\033[" << y << ";" << x << "f" << flush;
	}

#endif


	//Funkcja wypisywania instrukcji do gry w szachy
void Interface::menu()
{
	short centerPosition = 10;

	gotoXY(centerPosition,0); //wysrodkowanie
	cout<<"Witaj w programie szachowym!"<<endl;
	cout<<"Aby wyswietlic instrukcje gry wpisz polecenie 'HELP'"<<endl;
	cout<<"Aby zakonczyc rozgrywke wpisz polecenie 'QUIT'"<<endl;

}

void Interface::help(){

	cout<<"Ruch wybranej figury dokonujemy poprzez podanie jej wspolrzednych\n";
	cout<<"odpowiadajacych pozycji na szachownicy. Pierwsza wspolrzedna - duza\n";
	cout<<"litera, odpowiada kolumnie a druga liczba odpowiada wierszowi.\n";
	cout<<"Przykladowo wspolrzedne A1 odpowiadaja polu w pierwszym rzedzie i\n";
	cout<<"pierszej kolumnie. Uzytkownik moze podawac wspolrzedne zarowno malymi\n";
	cout<<"jak i duzymi literami. Ruchy wykonujemy do rezygnacji z gry."<<endl;
	cout<<endl<<"Wcisnij ENTER by powrocic do gry"<<endl;

	//Oczekiwanie na enter
	while (getchar() != '\n'){}

	short firstLineToClear = 17;
	int quantityLineToClear = 10;

	for (int i=0; i <= quantityLineToClear; i++)
	{
		clearLine(firstLineToClear+i);
	}
}

void Interface::draw(char board[BOARD_SIZE][BOARD_SIZE])
{
	short firstLine = 4;

    Interface::gotoXY(0, firstLine);

    char fieldName = 'A';	//Zmienna uzyta do wypisania rzedu liter, okreslajacych poszczegolne pola szachownicy


	cout<< "   ";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << fieldName << " ";
		fieldName++;
	}
	cout << endl << "  ----------------" << endl;

	for (int i = BOARD_SIZE - 1; i >= 0; i--)
	{

		cout << i+1 << "| ";

		for (unsigned j = 0; j < BOARD_SIZE; j++)
		{

			cout << board[i][j]<<" ";
		}

		cout << "|" << i+1 << endl;
	}

	fieldName = 'A';	//Zmienna uzyta do wypisania rzedu liter, okreslajacych poszczegolne pola szachownicy
	cout << "  ----------------" << endl;
	cout<< "   ";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << fieldName << " ";
		fieldName++;
	}

	cout<<endl;
}

std::string Interface::checkCommands(std::string command)
{
    string temporaryCommand="";
    std::string modyfiedCommand="";
	for(size_t i = 0; i < command.length(); i++ )
	{
		if(isalpha(command[i])){
                if(isupper(command[i]))
                {
                     command[i]=tolower(command[i]);
                }
			temporaryCommand+= command[i];
		}

	}
	return temporaryCommand;
}

void Interface::clearLine(short y)
{
	short consoleWidth = 128;

	Interface::gotoXY(0, y);
	cout << setw(consoleWidth) << " ";
	Interface::gotoXY(0, y);
}

Interface::~Interface() {
	// TODO Auto-generated destructor stub
}

