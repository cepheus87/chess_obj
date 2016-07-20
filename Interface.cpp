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
/*
	//void Interface::draw(char board[BOARD_SIZE][BOARD_SIZE],const Interface& inter)
	void Interface::draw(Board& boardObj)
	{

		char board[BOARD_SIZE][BOARD_SIZE];
		boardObj.getBoard(&board);

		cout<<"aaa "<<board[0][0]<<endl;
		cout<<"aaa "<<board[8][8]<<endl;

		short firstLine = 4;

	    gotoXY(0, firstLine);

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
*/
Interface::~Interface() {
	// TODO Auto-generated destructor stub
}

