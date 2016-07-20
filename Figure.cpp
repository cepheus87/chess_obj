/*
 * Figure.cpp
 *
 *  Created on: 19 lip 2016
 *      Author: Micha³
 */

#include "Figure.h"
#include "Board.h"

using namespace std;

Figure::~Figure() {
	// TODO Auto-generated destructor stub
}

Figure::Figure(char chessPiece) {
	fChessPiece = chessPiece;
	fWhite = isWhite(chessPiece);
}

inline bool Figure::isWhite(char chessPiece)
{
	return (chessPiece > 'A' && chessPiece < 'Z');
}



bool Figure::move(std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj ){

	  char c = fChessPiece;

	  bool returnStatement = true;

	  switch(c){

	  case 'p':
	  case 'P':
//	    returnStatement = movePawn();
	    break;

	  case 'r':
	  case 'R':
	//    returnStatement = moveRook();
	    break;

	  case 'n':
	  case 'N':
	  //  returnStatement = moveKnight();
	    break;

	  case 'b':
	  case 'B':
	    //returnStatement = moveBishop();
	    break;

	  case 'q':
	  case 'Q':
	    //returnStatement = moveQueen();
	    break;

	  case 'k':
	  case 'K':
	    returnStatement = moveKing(startPos, endPos, boardObj );
	    break;

	  default :
	    cout<<"Pole startowe jest puste"<<endl;
	    returnStatement = false;
	    break;
	  }

	  return returnStatement;

	}

bool Figure::isYour(std::pair<int,int> endPos, Board& board )
{
	if(! board.isEmpty(endPos ) )
	{	//Figure fig(board.getChessPiece(endPos));
		if(fWhite == isWhite(board.getChessPiece(endPos)) )
		{
			cout<<"Nie mozesz poruszyc sie na swoje pole";
			return false;
		}
		else return true;

	}
	else return true;
}


bool Figure::moveKing(std::pair<int,int> startPos, std::pair<int,int> endPos, Board& board ){


  if( abs(endPos.first - startPos.first) <= 1 && abs(endPos.second - startPos.second) <=1 ){
    return true;
  }
  else{
    cout<<"To nie jest dozwolony ruch krolem"<<endl;
    return false;
  }

}
