#include <qDebug>

#define TESTGAME


#ifdef TESTGAME
#include "test/testGame.h"
#endif // TESTGAME

int main() {
	testGame();
	return 0;
}
