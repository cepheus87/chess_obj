/*
 * Computer.cpp
 *
 *  Created on: 21 lip 2016
 *      Author: Micha³
 */

#include "Computer.h"

Computer::Computer() {
	// TODO Auto-generated constructor stub

}

std::string Computer::generate(Board &board)
{
	std::string x = "rr";

	xStart = (rand() % 8);
	yStart = (rand() % 8);

	//if()

	xEnd = (rand() % 8);
	yEnd = (rand() % 8);

	return x;

}

Computer::~Computer() {
	// TODO Auto-generated destructor stub
}

