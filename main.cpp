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


	inter.draw(board);

	cin.ignore();
}
