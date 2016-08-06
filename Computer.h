/*
 * Computer.h
 *
 *  Created on: 21 lip 2016
 *      Author: Micha³
 */

#include <string>
#include <time.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "Board.h"
#include "Figure.h"

#ifndef COMPUTER_H_
#define COMPUTER_H_

class Computer {
public:
	Computer(bool);

	std::string generate(Board &);
	void changePlayWithComputer();
	bool getPlayWithComputer();
	virtual ~Computer();

private:

	int xStart;
	int yStart;
	int xEnd;
	int yEnd;

	bool playWithComputer;
};

#endif /* COMPUTER_H_ */
