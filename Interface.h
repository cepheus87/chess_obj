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

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

class Interface {
public:
	Interface();
	virtual ~Interface();
	void gotoXY(short,short) const;
	void draw(Board &);
	void menu();
	void help();
	void clearLine(short y);
	std::string checkCommands(std::string);
	void changeFigurePosition(int,int,int,int,char);
};

#endif /* INTERFACE_H_ */
