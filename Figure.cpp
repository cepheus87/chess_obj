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

Figure::Figure(char chessPiece, bool mPlayer) {
	fChessPiece = chessPiece;
	fWhite = isWhite(chessPiece);
	player = mPlayer;
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

		returnStatement = movePawn(startPos, endPos, boardObj);
	    break;

	  case 'r':
	  case 'R':
	    returnStatement = moveRook(startPos, endPos, boardObj);
	    break;

	  case 'n':
	  case 'N':

	    returnStatement = moveKnight(startPos, endPos, boardObj);
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
		  if(boardObj.getComputerPlayer())
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
			if(board.getComputerPlayer())
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
	  if(board.getComputerPlayer())
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
		if(boardObj.getComputerPlayer())
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
				if(boardObj.getComputerPlayer())
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
				if(boardObj.getComputerPlayer())
					cout<<"Droga ruchu w poziomie nie jest pusta"<<endl;
				return false;
			}
			x+=direction;
		}
	}

	return true;
}

bool Figure::movePawn(std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj )
{

	char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	if (startPos.second == endPos.second)
	{
		if (board[endPos.first][endPos.second] != '.')
		{
			//if(boardObj.getComputerPlayer())
				cout<<"Droga ruchu w pionie nie jest pusta."<<endl;
			return false;
		}
		if (endPos.first - startPos.first == 2)
		{
			if ((player && startPos.first != 1) || (!player && startPos.first != 7 ))
			{
				//if(boardObj.getComputerPlayer())
					cout<<"Ruch z o dwa pola mozliwy tylko z wyjsciowej pozycji."<<endl;
			return false;
			}
		}
		else if (endPos.first - startPos.first > 1){
			//if(boardObj.getComputerPlayer())
				cout<<"To nie jest poprawny ruch pionka. Wykonaj ruch o jedno pole."<<endl;
			return false;
		}
		else if (board[(endPos.first + startPos.first) / 2][endPos.second] != '.')
		{
			//if(boardObj.getComputerPlayer())
				cout<<"To nie jest poprawny ruch pionka. Brak wolnej drogi."<<endl;
			return false;
		}

	}else
	{
		if ((abs(startPos.second - endPos.second) > 1))
		{
			//if(boardObj.getComputerPlayer())
				cout<<"To nie jest poprawny ruch pionka. Pionek rusza sie do przodu."<<endl;
			return false;
		}
		else if (board[endPos.first][endPos.second] == '.')
		{
			//if(boardObj.getComputerPlayer())
				cout<<"To nie jest poprawny ruch pionka. Brak bicia."<<endl;
			return false;
		}

	}
	return true;
}

bool Figure::moveKnight (std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj )
{

	if ((abs(endPos.second - startPos.second) != 2 || abs(endPos.first - startPos.first) != 1) && (abs(endPos.first - startPos.first) != 2 || abs(endPos.second - startPos.second) != 1))
	{
		if(boardObj.getComputerPlayer())
			cout<<"Niepoprawny ruch skoczkiem.";
		return false;
	}else
		return true;
}
