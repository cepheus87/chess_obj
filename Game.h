/*
 * Game.h
 *
 *  Created on: 05.08.2016
 *      Author: qbba7
 */

#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "Figure.h"
#include "Interface.h"
#include "Computer.h"
#include "Gamelib.h"

#include <cstdlib>
#include <ctime>
#include <unistd.h>

class Game {
public:
	Game();
	virtual ~Game();

	void gameStart(Interface&, Board&, Computer&);
	void whoseMoveInformation(string&, Board&, Interface&, bool&);
	void menuCommands(string&, Interface&, char&);
	void checkAndCheckMateVerification(Figure&, bool&, Board&, Interface&,
			char&);
	void wrongCommand(Interface&, Board&);
	void pressEnterToContinue(Interface&);
	void playerMove(string&, string&, string&, Board&, bool&, Interface&,
			char&);
	void computerMove(Computer&, string&, string&, string&, Board&, bool&,
			Interface&, char&);
	int connect(Connector& c);
	int terminalGame(int playerNr, Connector& c, string commandMove,
			Interface& inter, Board&, bool player, char& exit);
	bool player1(Connector& c, string, Interface& inter, Board&, bool player,
			char& exit);
	bool player2(Connector& c, string, Interface& inter, Board&, bool player,
			char& exit);
	static inline void wait(const int maxSeconds) {
		sleep(rand() % maxSeconds + 1);
	}

};

#endif /* GAME_H_ */
