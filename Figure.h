#ifndef FIGURE_H_
#define FIGURE_H_

#include "Board.h"

using namespace std;

class Figure {
private:

	char fChessPiece;
	bool fWhite;
	bool player;

public:
	virtual ~Figure();
	Figure(char, bool);
	inline bool isWhite(char);
	bool move(bool, pair<int, int>, pair<int, int>, Board&);
	bool isYour(pair<int, int>, Board&);

	bool moveKing(bool check, pair<int, int>, pair<int, int>, Board&);
	bool moveRook(bool check, pair<int, int>, pair<int, int>, Board&);
	bool movePawn(bool, bool check, pair<int, int>, pair<int, int>, Board&);
	bool moveKnight(bool check, pair<int, int>, pair<int, int>, Board&);
	bool moveBishop(bool check, pair<int, int>, pair<int, int>, Board&);
	bool moveQueen(bool check, pair<int, int>, pair<int, int>, Board&);

	pair<int, int> findPiece(char, Board&);
	pair<int, int> isItCheck(bool, Board&);
	bool isItCheckMate(bool, pair<int, int>, Board&);
	pair<int, int> anythingGoThere(bool, bool, pair<int, int>, Board&);
	bool kingEscape(bool, pair<int, int>, Board&);
	bool kingCoveringByRQ(bool, pair<int, int>, Board&);
	bool kingCoveringByBQ(bool, pair<int, int>, Board&);
};

#endif /* FIGURE_H_ */

