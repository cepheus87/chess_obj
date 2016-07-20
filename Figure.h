/*
 * Figure.h
 *
 *  Created on: 19 lip 2016
 *      Author: Micha³
 */

#ifndef FIGURE_H_
#define FIGURE_H_

#include"Board.h"

class Figure
{
private:

	char fChessPiece;
	bool fWhite;
public:
	virtual ~Figure();
	Figure(char);
	inline bool isWhite(char);
	bool move(std::pair<int,int> , std::pair<int,int>, Board& );
	bool isYour(std::pair<int,int> endPos, Board& board );

	bool moveKing(std::pair<int,int>, std::pair<int,int>, Board& );
	bool moveRook(std::pair<int,int> startPos, std::pair<int,int> endPos, Board& board );

};

#endif /* FIGURE_H_ */
