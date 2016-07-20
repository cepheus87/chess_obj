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

Interface::~Interface() {
	// TODO Auto-generated destructor stub
}

