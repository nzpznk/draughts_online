#include <QApplication>
#include <qDebug>

//#define TESTGAME
//#define TESTNETWORK
#define TESTPIECEBTN

#ifdef TESTGAME
#include "test/testGame.h"
#endif // TESTGAME

#ifdef TESTNETWORK
#include "test/testnetwork.h"
#endif // TESTNETWORK

#ifdef TESTPIECEBTN
#include "test/testpiecebtn.h"
#include "UI/piecebtn.h"
void testPieceBtn() {
	TestPieceBtn* testBtn = new TestPieceBtn;
	testBtn->show();
}
#endif // TESTPIECEBTN

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

//	testGame();
//	testNetWork();
	testPieceBtn();

	return app.exec();
}
