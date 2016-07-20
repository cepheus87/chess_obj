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
	    returnStatement = moveRook(startPos, endPos, boardObj);
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

bool Figure::moveRook(std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj )
{

	char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);


	if( !( (startPos.first == endPos.first) || (startPos.second == endPos.second) ) )
	{
		cout<<"To nie jest poprawny ruch wieza"<<endl;
		return false;
	}
	else if(startPos.second == endPos.second)
	{
		int direction = (endPos.first - startPos.first > 0) ? 1 : -1;
		int y = startPos.first + direction;
		while(! (y == endPos.first) )
		{
			if (board[y][startPos.second] != '.')
			{
				cout<<"Droga ruchu w pionie nie jest pusta"<<endl;
				return false;
			}
			y += direction;
		}
	}
	else if(startPos.first == endPos.first)
	{
		int direction = (endPos.second - startPos.second > 0) ? 1 : -1;
		cout<<startPos.second<<" "<<endPos.second<<endl;
		int x = startPos.second + direction;
		while(! (x == endPos.second) )
		{
			if (board[startPos.first][x] != '.')
			{
				cout<<"Droga ruchu w poziomie nie jest pusta"<<endl;
				return false;
			}
			x+=direction;
		}
	}

	return true;
}
