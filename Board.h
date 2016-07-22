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


	int startXPostoDrow;
	int startYPostoDrow;
	int endXPostoDrow;
	int endYPostoDrow;
	char chosenFigure;

	bool computerPlayer;
	bool twoPlayers;

public:
	Board(bool, bool);
	virtual ~Board();
	void getBoard( char* []);
	int getBoardSize() const;
	bool checkMove(std::string&, Board&);
	void move(std::string, std::string, Board& ,bool &);
	void move(std::pair<int,int>, std::pair<int,int>, Board&, bool& );
	bool checkPlayer(std::pair<int,int>, char [BOARD_SIZE][BOARD_SIZE], bool &);
	std::pair<int,int> getPosition(std::string);

	int getStartXPostoDrow ();
	int getStartYPostoDrow ();
	int getEndXPostoDrow ();
	int getEndYPostoDrow ();
	char getChosenFigure ();
	bool getComputerPlayer();
	bool getTwoPlayers();

	void changeComputerPlayer();
	void changeTwoPlayers();

	char getChessPiece(std::string );
	char getChessPiece(std::pair<int,int>);
	bool isEmpty(std::pair<int,int>);

};

#endif /* BOARD_H_ */
