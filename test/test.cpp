#include <QApplication>
#include <qDebug>

//#define TESTGAME
#define TESTNETWORK

#ifdef TESTGAME
#include "test/testGame.h"
#endif // TESTGAME

#ifdef TESTNETWORK
#include "test/testnetwork.h"
#endif // TESTNETWORK

//int main(int argc, char *argv[]) {
//	QApplication app(argc, argv);

////	testGame();
//	testNetWork();

//	return app.exec();
//}
