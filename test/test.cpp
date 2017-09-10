#include <QApplication>
#include <QObject>
#include <QDebug>

#define TEST

#ifdef TEST

//#define TESTGAME
//#define TESTNETWORK
//#define TESTPIECEBTN
//#define TESTDRAUGHTSBOARD
#define TESTCOMBINED

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


#ifdef TESTDRAUGHTSBOARD
#include "test/testdraughtsboard.h"
#include "UI/draughtsboard.h"
void testDraughtsBoard() {
	auto board = new DraughtsBoard;
	auto test = new TestDraughtsBoard;
	QObject::connect(test, SIGNAL(showPieceMsg(QVector<QVector<Piece> >)), board, SLOT(initWithMat(QVector<QVector<Piece> >)));
	board->show();
	test->show();
}
#endif //TESTDRAUGHTSBOARD

#ifdef TESTCOMBINED
#include "UI/draughtsboard.h"
#include "UI/welcome.h"
#include "server/server.h"
#include "client/client.h"

void testCombined() {

}

#endif //TESTCOMBINED

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

//	testGame();
//	testNetWork();
//	testPieceBtn();
	testDraughtsBoard();

	return app.exec();
}

#endif //TEST
