#ifndef TESTGAME_H
#define TESTGAME_H

#include "logic/game.h"

void testGame() {
	Game game;
	game.initGame("./normal.txt");
	auto ans = game.getAvaliableRoute(QPair<int, int>(1, 3));
	game.initGame("./king.txt");
	ans = game.getAvaliableRoute(QPair<int, int>(2, 2));
	ans = game.getAvaliableRoute(QPair<int, int>(6, 7));
	ans = game.nonEatRoute(QPair<int, int>(6, 7));
	ans = game.nonEatRoute(QPair<int, int>(1, 8));
	ans = game.getAvaliableRoute(QPair<int, int>(1, 8));
}

#endif // TESTGAME_H
