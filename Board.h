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



const int BOARD_SIZE = 8;

class Board
{

private:
	char* fBoard;

	int fBoardSize;

	void allocBoardMem();
	void init(char [BOARD_SIZE][BOARD_SIZE]);
	bool isAllowed(std::pair<int,int>, char [BOARD_SIZE][BOARD_SIZE], bool);
	bool isEmpty(std::pair<int,int>, char board[BOARD_SIZE][BOARD_SIZE] );
	std::pair<int,int> getPosition(std::string);

	int startXPostoDrow;
	int startYPostoDrow;
	int endXPostoDrow;
	int endYPostoDrow;
	char chosenFigure;

public:
	Board();
	virtual ~Board();
	void getBoard( char* []);
	int getBoardSize() const;
	bool checkMove(std::string&, Board&);
	void move(std::string, std::string, Board& ,bool &);
	void move(std::pair<int,int>, std::pair<int,int>, Board&, bool& );
	bool checkPlayer(std::pair<int,int>, char [BOARD_SIZE][BOARD_SIZE], bool &);

	int getStartXPostoDrow ();
	int getStartYPostoDrow ();
	int getEndXPostoDrow ();
	int getEndYPostoDrow ();
	char getChosenFigure ();

};

#endif /* BOARD_H_ */
