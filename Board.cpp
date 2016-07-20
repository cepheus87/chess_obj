/*
 * Board.cpp
 *
 *  Created on: 19 lip 2016
 *      Author: Micha³
 */

#include "Board.h"

using namespace std;

Board::Board() {
	// TODO Auto-generated constructor stub
}

void Board::init(char board[BOARD_SIZE][BOARD_SIZE])
{

    const char figuresRow[BOARD_SIZE] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};

	memset(board, '.', sizeof(char) * BOARD_SIZE * BOARD_SIZE);

    for (unsigned i = 0; i < BOARD_SIZE; i++)
        board[0][i] = figuresRow[i];

    for (unsigned i = 0; i < BOARD_SIZE; i++)
        board[1][i] = 'P';

    for (unsigned i = 0; i < BOARD_SIZE; i++)
        board[BOARD_SIZE - 2][i] = 'p';

    for (unsigned i = 0; i < BOARD_SIZE; i++)
        board[BOARD_SIZE - 1][i] = tolower(figuresRow[i]);

}

void Board::draw(char board[BOARD_SIZE][BOARD_SIZE],const Interface& inter)
{
	short firstLine = 4;

    inter.gotoXY(0, firstLine);

    char fieldName = 'A';	//Zmienna uzyta do wypisania rzedu liter, okreslajacych poszczegolne pola szachownicy


	cout<< "   ";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << fieldName << " ";
		fieldName++;
	}
	cout << endl << "  ----------------" << endl;

	for (int i = BOARD_SIZE - 1; i >= 0; i--)
	{

		cout << i+1 << "| ";

		for (unsigned j = 0; j < BOARD_SIZE; j++)
		{

			cout << board[i][j]<<" ";
		}

		cout << "|" << i+1 << endl;
	}

	fieldName = 'A';	//Zmienna uzyta do wypisania rzedu liter, okreslajacych poszczegolne pola szachownicy
	cout << "  ----------------" << endl;
	cout<< "   ";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << fieldName << " ";
		fieldName++;
	}

	cout<<endl;
}


std::pair<bool, std::string> Board::checkMove(std::string positions, char board[BOARD_SIZE][BOARD_SIZE])
{
	string quantityOfCharacters="";
	pair<bool, string> moveCorrectness(true, "");

	for(size_t i = 0; i < positions.length(); i++ )
	{
		if(isalpha(positions[i])){
			quantityOfCharacters+= positions[i];
		}
		if(isdigit(positions[i])){
			quantityOfCharacters+= positions[i];
		}

	}

	#ifdef DEBUG
		cout << "quantityOfCharacters: "<<quantityOfCharacters<<endl;
	#endif

	if(quantityOfCharacters.length()!=4){

		if(quantityOfCharacters.length()==3||quantityOfCharacters.length()==2)
		            {
		            cout<<"Wprowadziles " <<quantityOfCharacters.length()<<" znaki typu litera lub cyfra, powinny byc 4!";
		            }else if (quantityOfCharacters.length()==0)
		            {
		            cout<<"Wprowadziles " <<quantityOfCharacters.length()<<" liter i cyfr, powinny byc 4!";
		            }else if (quantityOfCharacters.length()==1)
		            {
		            cout<<"Wprowadziles " <<quantityOfCharacters.length()<<" litere lub cyfre, powinny byc 4!";
		            } else{
		            cout<<"Wprowadziles " <<quantityOfCharacters.length()<<" znakow typu litera lub cyfra, powinny byc tylko 4!";
		            }

		moveCorrectness.first= false;
		return moveCorrectness;
	}

	bool checkChar = true;

	for(size_t i = 0; i < quantityOfCharacters.length(); i++)
	{
		if ( i%2 == 0 )
		{
			if ( (atoi(&quantityOfCharacters[i])) == 0)
			{

				char castedChar = quantityOfCharacters[i];

				if(!((castedChar >= 'A' && castedChar <='A'+BOARD_SIZE)||(castedChar >= 'a' && castedChar <= 'a'+BOARD_SIZE))) // 65 == A
				{
					cout << "Litera na pozycji " << i+1 << " powinna byc z zakresu A-H lub a-h!" << endl;
					checkChar = false;
				}

			}else{

				cout<<"Znak "<<i+1<<" powinien byc litera a jest cyfra!"<<endl;
				moveCorrectness.first= false;

			}
		}
		else
		{

			if ( ( atoi(&quantityOfCharacters[i] ) < 1 )||( atoi(&quantityOfCharacters[i])>8 ) )
			{

				cout << "Liczba na pozycji " << i+1 << " powinna byc z zakresu 1-8!" << endl;
				checkChar = false;

			}
		}

	}

	std::string startPosition = quantityOfCharacters.substr(0,2);
	pair<int,int> startPos = getPosition(startPosition);

		if (isEmpty(startPos, board))
		{
	    cout<<"To pole jest puste."<<endl;
	    moveCorrectness.first= false;
	    return moveCorrectness;
		}

	if (checkChar == false)
	{
		moveCorrectness.first= false;
		return moveCorrectness;
	}

	moveCorrectness.second=quantityOfCharacters;
	return moveCorrectness;
}

bool Board::isAllowed(std::pair<int,int> endPos, char board[BOARD_SIZE][BOARD_SIZE], bool player)
{

	if (player)
	{
		if( (board[endPos.first][endPos.second] >= 'A') && (board[endPos.first][endPos.second] <= 'Z') )
		{
			cout<<"Nie mozesz wykonac ruchu na swoje pole."<<endl;

			return false;

		}
		else
		{

			return true;
		}


	}else{


		if( (board[endPos.first][endPos.second] >= 'a') && (board[endPos.first][endPos.second] <= 'z') )
		{
			cout<<"Nie mozesz wykonac ruchu na swoje pole."<<endl;

			return false;

		}
		else
		{

			return true;

		}
	}
}

std::pair<int,int> Board::getPosition(std::string pos)
{
	pair<int, int> posPair;
	const char* firstChar = &pos.at(0);
	const char* secondChar = &pos.at(1);
		if ( (atoi(firstChar)) != 0)
		{
			posPair.first= atoi(firstChar) - 1;
			char castedChar = secondChar[0];
			if(castedChar >= 'A' && castedChar <='H') // 65 == A
			{
				posPair.second = castedChar - 'A';
			}
			else
			{
				posPair.second = castedChar - 'a';  // 97 == a
			}
		}
		else
		{

			posPair.first= atoi(secondChar) - 1;
			char castedChar = firstChar[0];

			if(castedChar >= 'A' && castedChar <= 'H') // 65 == A
			{
				posPair.second=castedChar - 'A';
			}
			else
			{
				posPair.second=castedChar - 'a';  // 97 == a
			}

		}

		return posPair;
}

bool Board::isEmpty(std::pair<int,int> endPos, char board[BOARD_SIZE][BOARD_SIZE] )
{
  if( board[endPos.first][endPos.second] == '.') return true;
  else return false;
}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

