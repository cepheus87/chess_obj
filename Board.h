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


#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

const int BOARD_SIZE = 8;

class Board
{

public:
	Board();
	virtual ~Board();

	void init(char [BOARD_SIZE][BOARD_SIZE]);
	bool checkMove(std::string &, char [BOARD_SIZE][BOARD_SIZE]);

private:
	bool isAllowed(std::pair<int,int>, char [BOARD_SIZE][BOARD_SIZE], bool);
	bool isEmpty(std::pair<int,int>, char board[BOARD_SIZE][BOARD_SIZE]);
	std::pair<int,int> getPosition(std::string);


};

#endif /* BOARD_H_ */
