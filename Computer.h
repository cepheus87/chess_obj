/*
 * Computer.h
 *
 *  Created on: 21 lip 2016
 *      Author: Micha³
 */

#include <string>
#include "Board.h"
#include "Figure.h"

#ifndef COMPUTER_H_
#define COMPUTER_H_

class Computer {
public:
	Computer();
	std::string generate(Board &);
	virtual ~Computer();

private:
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;
};

#endif /* COMPUTER_H_ */
