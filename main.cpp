#include "Board.h"
#include "Figure.h"
#include "Interface.h"

using namespace std;

int main(int argc, char* argv[])
{

	#ifndef _WIN32
	system("clear");
	#endif

	Interface inter;
	Board board;

	char* tempTable;
	board.getBoard(&tempTable);



	cout<<tempTable[0]<<endl;
		cout<<tempTable[8*8-1]<<endl;

	//inter.draw(board);

	cin.ignore();
}
