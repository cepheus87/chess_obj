/*
 * Interface.h
 *
 *  Created on: 19 lip 2016
 *      Author: Micha³
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <utility>
#include <cstdio>
#include <sstream>
#include <cctype>
#include <iomanip>

#include "Board.h"
#include "Computer.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class Interface {
private:
	bool terminalMode;
public:
	Interface();
	virtual ~Interface();
	void gotoXY(short, short) const;
	void draw(Board &);
	void menu();
	void help();
	void gameType(Board&, Computer&);
	void clearLine(short y);
	void clearScreen();
	string checkCommands(string);
	void changeFigurePosition(Board &);
	bool getTerminalMode();
};

#endif /* INTERFACE_H_ */
