#ifndef FIGURE_H_
#define FIGURE_H_

#include "Board.h"

class Figure
{
private:

	char fChessPiece;
	bool fWhite;
	bool player;

public:
	virtual ~Figure();
	Figure(char, bool);
	inline bool isWhite(char);
	bool move(bool,std::pair<int,int> , std::pair<int,int>, Board& );
	bool isYour(std::pair<int,int>, Board& );

	bool moveKing(bool check,std::pair<int,int>, std::pair<int,int>, Board& );
	bool moveRook(bool check,std::pair<int,int>, std::pair<int,int>, Board& );
	bool movePawn(bool,bool check,std::pair<int,int>, std::pair<int,int>, Board& );
	bool moveKnight(bool check,std::pair<int,int>, std::pair<int,int>, Board& );
	bool moveBishop(bool check,std::pair<int,int>, std::pair<int,int>, Board&);
	bool moveQueen(bool check,std::pair<int,int>, std::pair<int,int>, Board&);

	std::pair<int,int> findPiece(char,Board&);
	std::pair<int,int> isItCheck(bool,Board&);
	bool isItCheckMate(bool,std::pair<int,int>, Board&);
	std::pair<int,int> anythingGoThere(bool,bool,std::pair<int,int>,Board&);
	bool kingEscape(bool,std::pair<int,int> ,Board&);
	bool kingCoveringByRQ(bool,std::pair<int,int>,Board&);
	bool kingCoveringByBQ(bool,std::pair<int,int>,Board&);
};

#endif /* FIGURE_H_ */

