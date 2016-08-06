/*
 * Computer.cpp
 *
 *  Created on: 21 lip 2016
 *      Author: Micha³
 */

#include "Computer.h"

using namespace std;

Computer::Computer(bool playWithCPU) {

	xStart = 1;
	yStart = 1;
	xEnd = 1;
	yEnd = 1;

	playWithComputer = playWithCPU;
}

void Computer::changePlayWithComputer() {
	playWithComputer = !playWithComputer;
}

bool Computer::getPlayWithComputer() {
	return playWithComputer;
}

	string Computer::generate(Board &boardObj) {
	char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] =
			reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	string generatedMove = "    ";
	srand(time(NULL));
	while (1) {
		xStart = (rand() % 8);
		yStart = (rand() % 8);
		//if( (board[xStart][yStart] > 'a') && (board[xStart][yStart] < 'z') ) {
		if ((board[yStart][xStart] == 'r') || (board[yStart][xStart] == 'n')
				|| (board[yStart][xStart] == 'b')
				|| (board[yStart][xStart] == 'q')
				|| (board[yStart][xStart] == 'k')
				|| (board[yStart][xStart] == 'p')) {
			int xSt = xStart;
			int ySt = yStart;
			generatedMove.at(0) = xSt + 'a';
			generatedMove.at(1) = ySt + '1';
			break;
		}
	}

	while (1) {
		xEnd = (rand() % 8);
		yEnd = (rand() % 8);
		//if( ((board[yEnd][xEnd] > 'A') && (board[yEnd][xEnd] < 'Z')) || (board[yEnd][xEnd] == '.') ) {
		if (board[yEnd][xEnd] == '.') {
			int xEn = xEnd;
			int yEn = yEnd;

			generatedMove.at(2) = xEn + 'a';
			generatedMove.at(3) = yEn + '1';
			break;
		}
	}
	return generatedMove;
}

Computer::~Computer() {
	// TODO Auto-generated destructor stub
}

