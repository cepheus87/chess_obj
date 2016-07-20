/*
 * BOARD.h
 *
 *  Created on: 19 lip 2016
 *      Author: Micha³
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <utility>
#include <cstdio>
#include <sstream>
#include <cctype>
#include <iomanip>
#include "Interface.h"

#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

const int BOARD_SIZE = 8;

class Board
{

private:
	void init(char [BOARD_SIZE][BOARD_SIZE]);
	void draw(char [BOARD_SIZE][BOARD_SIZE], const Interface&);
	bool isAllowed(std::pair<int,int>, char [BOARD_SIZE][BOARD_SIZE], bool);
	bool isEmpty(std::pair<int,int>, char board[BOARD_SIZE][BOARD_SIZE] );
	std::pair<bool,std::string> checkMove(std::string,char [BOARD_SIZE][BOARD_SIZE]);
	std::pair<int,int> getPosition(std::string);

public:
	Board();
	virtual ~Board();
};

#endif /* BOARD_H_ */
