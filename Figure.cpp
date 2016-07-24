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



bool Figure::move(bool whitePlayer, std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj ){

	  char c = fChessPiece;

	  bool returnStatement = true;

	  switch(c){

	  case 'p':
	  case 'P':

		returnStatement = movePawn(whitePlayer, false,startPos, endPos, boardObj);
	    break;

	  case 'r':
	  case 'R':
	    returnStatement = moveRook(false,startPos, endPos, boardObj);
	    break;

	  case 'n':
	  case 'N':

	    returnStatement = moveKnight(false,startPos, endPos, boardObj);
	    break;

	  case 'b':
	  case 'B':
	    returnStatement = moveBishop(false,startPos, endPos, boardObj);
	    break;

	  case 'q':
	  case 'Q':
	    returnStatement = moveQueen(false,startPos, endPos, boardObj);
	    break;

	  case 'k':
	  case 'K':
	    returnStatement = moveKing(false,startPos, endPos, boardObj );
	    break;

	  default :
		  if( boardObj.getComputerPlayer() || boardObj.getTwoPlayers() )
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
			if( board.getComputerPlayer() || board.getTwoPlayers() )
				cout<<"Nie mozesz poruszyc sie na swoje pole";
			return false;
		}
		else return true;

	}
	else return true;
}


bool Figure::moveKing(bool check, std::pair<int,int> startPos, std::pair<int,int> endPos, Board& board ){


  if( abs(endPos.first - startPos.first) <= 1 && abs(endPos.second - startPos.second) <=1 ){
    return true;
  }
  else{
	  if( (board.getComputerPlayer() || board.getTwoPlayers())&&!check )
		  cout<<"To nie jest dozwolony ruch krolem"<<endl;
    return false;
  }

}

bool Figure::moveRook(bool check, std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj )
{

	char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);


	if( !( (startPos.first == endPos.first) || (startPos.second == endPos.second) ) )
	{
		if((boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check)
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
				if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
					cout<<"Droga ruchu w pionie nie jest pusta"<<endl;
				return false;
			}
			y += direction;
		}
	}
	else if(startPos.first == endPos.first)
	{
		int direction = (endPos.second - startPos.second > 0) ? 1 : -1;
		//cout<<startPos.second<<" "<<endPos.second<<endl;
		int x = startPos.second + direction;
		while(! (x == endPos.second) )
		{
			if (board[startPos.first][x] != '.')
			{
				if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
					cout<<"Droga ruchu w poziomie nie jest pusta"<<endl;
				return false;
			}
			x+=direction;
		}
	}

	return true;
}

bool Figure::movePawn(bool whitePlayer, bool check,std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj )
{

	char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	if (startPos.second == endPos.second)
	{
		if (((endPos.first - startPos.first)<0&&whitePlayer)||((startPos.first - endPos.first)<0&&!whitePlayer))
        {
            if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
                    cout<<"To nie jest poprawny ruch pionka. Pionek nie porusza sie do tylu."<<endl;
            return false;
        }
		if (board[endPos.first][endPos.second] != '.')
		{
			if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
				cout<<"Droga ruchu w pionie nie jest pusta."<<endl;
			return false;
		}
		if (abs(endPos.first - startPos.first) == 2)
		{
			if ((player && startPos.first != 1) || (!player && startPos.first != 6 ))
			{
				if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
					cout<<"Ruch z o dwa pola mozliwy tylko z wyjsciowej pozycji."<<endl;
			return false;
			}

			if (board[(endPos.first + startPos.first) / 2][endPos.second] != '.')
			{
				if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
					cout<<"To nie jest poprawny ruch pionka. Brak wolnej drogi."<<endl;
				return false;
			}


		}else if ((abs(endPos.first - startPos.first)) > 2){
			if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
				cout<<"To nie jest poprawny ruch pionka. Wykonaj ruch o jedno pole."<<endl;
			return false;

		}

	}else
	{
		if ((abs(startPos.second - endPos.second) >1))
         {

			if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
				cout<<"To nie jest poprawny ruch pionka. Pionek rusza sie do przodu."<<endl;
			return false;
		}else if ((abs(startPos.second - endPos.second) ==1)&&((abs(endPos.first - startPos.first)) > 1))
		{
		    return false;
		}

		else if ((abs(startPos.second - endPos.second) ==1)&&(board[endPos.first][endPos.second] != '.')&&(startPos.first - endPos.first) ==0)
		{
		    if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
		    cout<<"Nie mozna zbic przeciwnika w bok"<<endl;
		    return false;
		}

		else if (board[endPos.first][endPos.second] == '.')
		{
			if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
				cout<<"To nie jest poprawny ruch pionka. Brak bicia."<<endl;
			return false;
		}

		else if (((endPos.first - startPos.first)<0&&player)||((startPos.first - endPos.first)<0&&!player))
        {
            if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
                cout<<"To nie jest poprawny ruch pionka. Pionek nie porusza siê do tylu."<<endl;
            return false;
        }
	}
	return true;
}


bool Figure::moveKnight (bool check, std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj )
{

	if ((abs(endPos.second - startPos.second) != 2 || abs(endPos.first - startPos.first) != 1) && (abs(endPos.first - startPos.first) != 2 || abs(endPos.second - startPos.second) != 1))
	{
		if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
			cout<<"Niepoprawny ruch skoczkiem.";
		return false;
	}else
		return true;
}

bool Figure::moveBishop(bool check,std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj ) {

	char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	if( abs(endPos.first - startPos.first) != abs(endPos.second - startPos.second) ) {
		if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
			cout << "To nie jest poprawny ruch dla gonca!" << endl;
		return false;
	}
	else {
		int dirX = (endPos.first - startPos.first > 0) ? 1 : -1;
		int dirY = (endPos.second - startPos.second > 0) ? 1 : -1;
		int x = startPos.first + dirX;
		int y = startPos.second + dirY;

		while(! (x == endPos.first) ) {
			if (board[x][y] != '.') {
				if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check )
					cout << "Droga ruchu figury nie jest pusta!" << endl;
				return false;
			}
			x += dirX;
			y += dirY;
		}
	}
	return true;
}

bool Figure::moveQueen(bool check, std::pair<int,int> startPos, std::pair<int,int> endPos, Board& boardObj ) {

	if (moveRook(check,startPos, endPos, boardObj) || moveBishop(check,startPos, endPos, boardObj)) {
		return true;
	}
	else {
		if( (boardObj.getComputerPlayer() || boardObj.getTwoPlayers())&&!check)
			cout << "To nie jest poprawny ruch krolowej!" << endl;
		return false;
	}

}


//Funkcja do sprawdzania czy nie wystepuje szach, zwraca ile pionkow szachuje
std::pair<int,int> Figure::isItCheck(bool whitePlayer,Board& boardObj)
{
	//Szukanie pozycji krola przeciwnika
	std::pair<int,int> kingPosition;
	if(whitePlayer){
        kingPosition=findPiece('k',boardObj);
	} else {
	    kingPosition=findPiece('K',boardObj);
	}
	return anythingGoThere(false,whitePlayer,kingPosition,boardObj);
}

//Sprawdzanie czy ktokolwiek moze wejsc na podane pole.
//whitePlayer - zaleznie od tego czy przeciwna druzyna proboje zbic ten kolor
std::pair<int,int> Figure::anythingGoThere(bool withoutKing,bool whitePlayer, std::pair<int,int> position, Board& boardObj)
{
    char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

    short checksCounter=0; //ilosc figur szachujacych
    pair<int,int>  piecePosition;
    pair<int,int> checkingPosition;
    for(int x=1; x<9; x++)
    {
        for(int y=0; y<8; y++)
        {
            ostringstream ss;
            string piecePos="";
            bool possibleCheck=false;

            if (board[x-1][y] != '.')
            {
                char firstPart='a'+y;
                piecePos+=firstPart;
                ss << x;
                piecePos += ss.str();
                piecePosition = boardObj.getPosition(piecePos);

                    switch(board[x-1][y])
                    {
                        case 'p':
                            if (!whitePlayer)
                                possibleCheck=movePawn(whitePlayer,true,piecePosition, position, boardObj );
                            break;
                        case 'P':
                            if (whitePlayer)
                                possibleCheck=movePawn(whitePlayer,true,piecePosition, position, boardObj );
                            break;

                        case 'r':
                            if (!whitePlayer)
                                possibleCheck=moveRook(true,piecePosition, position, boardObj );
                        break;
                        case 'R':
                            if (whitePlayer)
                                possibleCheck=moveRook(true,piecePosition, position, boardObj );
                        break;

                        case 'n':
                            if (!whitePlayer)
                                possibleCheck=moveKnight(true,piecePosition, position, boardObj );
                        break;
                        case 'N':
                            if (whitePlayer)
                                possibleCheck=moveKnight(true,piecePosition, position, boardObj );
                        break;

                        case 'b':
                            if (!whitePlayer)
                                possibleCheck=moveBishop(true,piecePosition, position, boardObj );
                        break;
                        case 'B':
                            if (whitePlayer)
                                possibleCheck=moveBishop(true,piecePosition, position, boardObj );
                        break;

                        case 'q':
                            if (!whitePlayer)
                                possibleCheck=moveQueen(true,piecePosition, position, boardObj );
                        break;
                        case 'Q':
                            if (whitePlayer)
                                possibleCheck=moveQueen(true,piecePosition, position, boardObj );
                        break;

                        case 'k':
                            if(!withoutKing)
                            {
                                if (!whitePlayer)
                                    possibleCheck=moveKing(true,piecePosition, position, boardObj );
                            }
                        break;
                        case 'K':
                            if(!withoutKing)
                            {
                                if (whitePlayer)
                                    possibleCheck=moveKing(true,piecePosition, position, boardObj );
                            }
                        break;

                        default :
                            cout<<"Jesli to widzisz, cos poszlo nie tak";
                        break;
                    }

                if (possibleCheck)      //naliczanie pionkow szachujacych.
                {
                    checkingPosition=piecePosition;
                    checksCounter++;
                }
            }
        }
    }

    if(checksCounter>1)
    {
        checkingPosition.first=200;//Kod dla dwoch figur szachujacych
        return checkingPosition;
    }else if (checksCounter==0)
    {
       checkingPosition.first=100;//Kod dla braku szachu
        return checkingPosition;
    }
return checkingPosition;
}

//Funkcja szukajaca pozycji konkretnego pionka
pair<int,int> Figure::findPiece(char piece, Board& boardObj)
{
    char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	pair<int,int> piecePosition;

    for(short x=0; x<8; x++)
    {
        for(short y=0; y<8; y++)
        {
            ostringstream ss;
            string piecePos="";
            char firstPart='a'+y;
            piecePos+=firstPart;
            ss << x+1;
            piecePos += ss.str();

            if(board[x][y] == piece)
                piecePosition = boardObj.getPosition(piecePos);
        }
    }
    return piecePosition;
}


bool Figure::isItCheckMate(bool whitePlayer,std::pair<int,int> checkingPosition,Board& boardObj)
{
    std::pair<int,int> kingPosition;
	if(whitePlayer){
        kingPosition=findPiece('k',boardObj);
	} else {
	    kingPosition=findPiece('K',boardObj);
	}

	//! 1) - Czy krol ma gdzie uciec?
	bool escape =kingEscape(whitePlayer, kingPosition,boardObj);
    bool beating;
    bool coveringByRQ;
    bool coveringByBQ;

    if(checkingPosition.first==200)
    {
            if(escape)
            {
                return true;
            }

    } else {
        //! 2) - Czy mozna zbic figure szachujaca?
        std::pair<int,int> pos=anythingGoThere(false,!whitePlayer,checkingPosition,boardObj);
        if(pos.first==100)  //Jesli nic nie moze zbic figury szachujacej
        {
            beating=true;
        } else
        {
            beating=false;
        }

        //!3) - Czy mozna zaslonic krola? (dotyczy to tylko sytuacji gdy szachuje wie¿a, goniec b¹dz krolowa
            coveringByRQ=kingCoveringByRQ(whitePlayer, checkingPosition,boardObj);
            coveringByBQ=kingCoveringByBQ(whitePlayer, checkingPosition,boardObj);

    }

    #ifdef DEBUG
    cout<<"cR="<<coveringByRQ<<" "<<endl;
    cout<<"cB="<<coveringByBQ<<" "<<endl;
    cout<<"b="<<beating<<" "<<endl;
    cout<<"e="<<escape<<" "<<endl;
    #endif

    if((!beating||!escape)||!coveringByRQ||!coveringByBQ)
    {
        return false;
    } else
    {
        return true;
    }
}

//! 1) - Czy krol ma gdzie uciec?
bool Figure::kingEscape(bool whitePlayer, std::pair<int,int> kingPosition,Board& boardObj)
{

    char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

    std::pair<int,int> possibleCheckMate;
    for(int x=(kingPosition.first-1);x<=(kingPosition.first+1);x++)
    {
        if(x>=0&&x<=7)
        {
            for(int y=(kingPosition.second-1);y<=(kingPosition.second+1);y++)
            {
                    if(y>=0&&y<=7)
                    {
                        if(board[x][y]=='.')
                        {
                            //Trzeba ukryc krola!
                            board[kingPosition.first][kingPosition.second]='.';

                            std::pair <int,int> escapePos;
                            escapePos.first=x;
                            escapePos.second=y;
                            possibleCheckMate=anythingGoThere(false,whitePlayer,escapePos, boardObj );

                            if(!whitePlayer)
                            {
                                board[kingPosition.first][kingPosition.second]='K';
                            }else{
                                board[kingPosition.first][kingPosition.second]='k';
                            }

                            if(possibleCheckMate.first==100)
                            {
                                return false; //Nie ma szacha matu - mozna uciec krolem
                            }
                        }
                    }

                }
        }
    }
return true; //Jest szach mat - nie mozna uciec  krolem
}

//! 3) - Czy mozna zaslonic krola? (dotyczy to tylko sytuacji gdy szachuje wie¿a, goniec b¹dz krolowa
//Blokowanie szachu poziomego lub pionowego
bool Figure::kingCoveringByRQ(bool whitePlayer,std::pair<int,int> checkPosition,Board& boardObj)
{

    char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	std::pair<int,int> kingPosition;
	if(whitePlayer){
        kingPosition=findPiece('k',boardObj);
	} else {
	    kingPosition=findPiece('K',boardObj);
	}

	std::pair<int,int> temporaryPos;
    char figure=board[checkPosition.first][checkPosition.second];

    //W pionie lub poziomie
    if((figure=='r')||(figure=='R')||(figure=='q')||(figure=='Q'))
    {
        if(checkPosition.first==kingPosition.first) //w tym samym wierszu
        {
            temporaryPos.first=checkPosition.first;
            short difference=(checkPosition.second-kingPosition.second);

            if(difference>0)//figura szachujacca na prawo od krola
            {
                difference--;
                for (int i=difference;i>0;i--)
                {
                    temporaryPos.second=checkPosition.second-i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }

            }else{ //figura szachujacca na lewo od krola
                difference++;
                for (int i=-difference;i>0;i--)
                {
                    temporaryPos.second=checkPosition.second+i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }
            }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

        }else if (checkPosition.second==kingPosition.second) //w tej samej kolumnie
        {
            temporaryPos.second=checkPosition.second;
            short difference=(checkPosition.first-kingPosition.first);

            if(difference>0)//figura szachujacca powyzej krola
            {
                difference--;
                for (int i=difference;i>0;i--)
                {
                    temporaryPos.first=checkPosition.first-i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }

            }else{ //figura szachujacca ponizej krola
                difference++;

                for (int i=-difference;i>0;i--)
                {
                    temporaryPos.first=checkPosition.first+i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }
            }

        }
        return true;
    }
    return true;
}

//Blokowanie szachu po skosie
bool Figure::kingCoveringByBQ(bool whitePlayer,std::pair<int,int> checkPosition,Board& boardObj)
{

    char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] = reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	std::pair<int,int> kingPosition;
	if(whitePlayer){
        kingPosition=findPiece('k',boardObj);
	} else {
	    kingPosition=findPiece('K',boardObj);
	}

	std::pair<int,int> temporaryPos;
    char figure=board[checkPosition.first][checkPosition.second];

    //W pionie lub poziomie
    if((figure=='b')||(figure=='B')||(figure=='q')||(figure=='Q'))
    {
        if(checkPosition.first<kingPosition.first) //poni¿ej krola
        {
            short difference=(checkPosition.second-kingPosition.second);
            if(difference>0)//figura szachujacca na prawo od krola
            {

                for (int i=difference-1;i>0;i--)
                {
                    temporaryPos.first=checkPosition.first+i;
                    temporaryPos.second=checkPosition.second-i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }

            }else{ //figura szachujacca na lewo od krola

                for (int i=(-difference)-1;i>0;i--)
                {
                    temporaryPos.first=checkPosition.first+i;
                    temporaryPos.second=checkPosition.second+i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }
            }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`

        }else if (checkPosition.second>kingPosition.second) //pionek powyzej krola
        {
            short difference=(checkPosition.second-kingPosition.second);
            if(difference>0)//figura szachujacca na prawo od krola
            {
                for (int i=difference-1;i>0;i--)
                {
                    temporaryPos.first=checkPosition.first-i;
                    temporaryPos.second=checkPosition.second-i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }
            }else{ //figura szachujacca na lewo od krola

                for (int i=difference-1;i>0;i--)
                {
                    temporaryPos.first=checkPosition.first-i;
                    temporaryPos.second=checkPosition.second+i;
                    if(anythingGoThere(true,!whitePlayer, temporaryPos,boardObj).first!=100)
                        return false;
                }
            }

        }
        return true;
    }
    return true;
}

