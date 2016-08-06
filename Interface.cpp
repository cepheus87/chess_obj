/*
 * Interface.cpp
 *
 *  Created on: 19 lip 2016
 *      Author: Micha³
 */

#include "Interface.h"

Interface::Interface() {
	// TODO Auto-generated constructor stub
	terminalMode = false;

}

#ifdef _WIN32

#define MOVE_X_LINUX_CORRECTION 0

void Interface::gotoXY(short x, short y) const {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#else

#define MOVE_X_LINUX_CORRECTION 1

void Interface::gotoXY(short x, short y) const
{
	cout << "\033[" << y << ";" << x << "f" << flush;
}

#endif

void Interface::changeFigurePosition(Board &boardObj) {
	int startXPostoDrow = boardObj.getStartXPostoDrow();
	int startYPostoDrow = boardObj.getStartYPostoDrow();

	int endXPostoDrow = boardObj.getEndXPostoDrow();
	int endYPostoDrow = boardObj.getEndYPostoDrow();

	char chosenFigure = boardObj.getChosenFigure();

	gotoXY(startXPostoDrow, startYPostoDrow);
	printf(".");
	gotoXY(endXPostoDrow, endYPostoDrow);
	printf("%c", chosenFigure);

}

//void Interface::draw(char board[BOARD_SIZE][BOARD_SIZE],const Interface& inter)
void Interface::draw(Board& boardObj) {

	char* tempTable;
	boardObj.getBoard(&tempTable);
	char (*board)[BOARD_SIZE] =
			reinterpret_cast<char (*)[BOARD_SIZE]>(tempTable);

	//cout<<board[0][0]<<endl;
	//cout<<board[7][7]<<endl;

	short firstLine = 4;

	gotoXY(0, firstLine);

	char fieldName = 'A';//Zmienna uzyta do wypisania rzedu liter, okreslajacych poszczegolne pola szachownicy

	cout << "   ";

	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << fieldName << " ";
		fieldName++;
	}
	cout << endl << "  ----------------" << endl;

	for (int i = BOARD_SIZE - 1; i >= 0; i--) {

		cout << i + 1 << "| ";

		for (unsigned j = 0; j < BOARD_SIZE; j++) {

			cout << board[i][j] << " ";
		}

		cout << "|" << i + 1 << endl;
	}

	fieldName = 'A';//Zmienna uzyta do wypisania rzedu liter, okreslajacych poszczegolne pola szachownicy
	cout << "  ----------------" << endl;
	cout << "   ";

	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << fieldName << " ";
		fieldName++;
	}

	cout << endl;

}

//Funkcja wypisywania instrukcji do gry w szachy
void Interface::menu() {
	short centerPosition = 10;

	gotoXY(centerPosition, 0); //wysrodkowanie
	cout << "Witaj w programie szachowym!" << endl;
	cout << "Aby wyswietlic instrukcje gry wpisz polecenie 'HELP'" << endl;
	cout << "Aby zakonczyc rozgrywke wpisz polecenie 'QUIT'" << endl;

}

void Interface::help() {

	cout
			<< "Ruch wybranej figury dokonujemy poprzez podanie jej wspolrzednych\n";
	cout
			<< "odpowiadajacych pozycji na szachownicy. Pierwsza wspolrzedna - duza\n";
	cout << "litera, odpowiada kolumnie a druga liczba odpowiada wierszowi.\n";
	cout
			<< "Przykladowo wspolrzedne A1 odpowiadaja polu w pierwszym rzedzie i\n";
	cout
			<< "pierszej kolumnie. Uzytkownik moze podawac wspolrzedne zarowno malymi\n";
	cout << "jak i duzymi literami. Ruchy wykonujemy do rezygnacji z gry."
			<< endl;
	cout << endl << "Wcisnij ENTER by powrocic do gry" << endl;

	//Oczekiwanie na enter
	while (getchar() != '\n') {
	}

	short firstLineToClear = 17;
	int quantityLineToClear = 10;

	for (int i = 0; i <= quantityLineToClear; i++) {
		clearLine(firstLineToClear + i);
	}
}

std::string Interface::checkCommands(std::string command) {
	string temporaryCommand = "";
	std::string modyfiedCommand = "";
	for (size_t i = 0; i < command.length(); i++) {
		if (isalpha(command[i])) {
			if (isupper(command[i])) {
				command[i] = tolower(command[i]);
			}
			temporaryCommand += command[i];
		}

	}
	return temporaryCommand;
}

void Interface::clearLine(short y) {
	short consoleWidth = 128;

	gotoXY(0, y);
	cout << setw(consoleWidth) << " ";
	gotoXY(0, y);
}

void Interface::clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void Interface::gameType(Board& board, Computer& comp) {

	string type = "";
	string wrongType = "Nie ma takiego trybu! Podaj jeszcze raz.";

	cout << "Witaj w programie szachowym!" << endl;
	;
	cout << "a) Gra z komputerem." << endl;
	cout << "b) Gra dla dwoch graczy." << endl;
	cout << "c) Gra na dwa terminale." << endl;
	cout << "Wybierz tryb gry: ";
	cin >> type;
	while (1) {

		string checkedGameType = checkCommands(type);

		if (checkedGameType == "a") { //computerPlayer ma byc true
			if (!board.getComputerPlayer()) {
				board.changeComputerPlayer();
			}
			if (!comp.getPlayWithComputer()) {
				comp.changePlayWithComputer();
			}
			getchar();
			clearScreen();
			break;
		}
		if (checkedGameType == "b") { //computerPlayer ma byc false
			if (board.getComputerPlayer()) {
				board.changeComputerPlayer();
				board.changeTwoPlayers();
			}
			getchar();
			clearScreen();
			break;
		}
		if (checkedGameType == "c") {
			if (board.getComputerPlayer()) {
				board.changeComputerPlayer();
				board.changeTwoPlayers();
			}
			terminalMode = true;
			getchar();
			clearScreen();
			break;
		}
		cout << wrongType << endl;
		gotoXY(18, 4);
		cout << setw(40) << " ";
		gotoXY(18, 4);
		cin >> type;
		clearLine(5);
	}
}

bool Interface::getTerminalMode() {
	return terminalMode;
}

Interface::~Interface() {
	// TODO Auto-generated destructor stub
}

