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

QDataStream& operator<< (QDataStream& out, const Message& msg) {
	out << msg.str;
	out << msg.vec;
	return out;
}

QDataStream& operator>> (QDataStream& in, Message& msg) {
	in >> msg.str;
	in >> msg.vec;
	return in;
}

void testCombined() {
	DraughtsBoard* board1 = new DraughtsBoard;
	Client* client1 = new Client;
	Server* server1 = new Server;
	Welcome* wel1 = new Welcome;
	QObject::connect(wel1, SIGNAL(initServerMsg(int)), server1, SLOT(initServer(int)));
	QObject::connect(wel1, SIGNAL(initClientMsg(QHostAddress,int)), client1, SLOT(connectHost(QHostAddress,int)));
	QObject::connect(wel1, SIGNAL(initGameMsg(QString)), client1, SLOT(startGame(QString)));
	QObject::connect(client1, SIGNAL(initDaughtsBoard(QVector<QVector<Piece> >)), board1, SLOT(initWithMat(QVector<QVector<Piece> >)));
	QObject::connect(client1, SIGNAL(updateAvaliableMsg(QSet<QPair<int,int> >,bool)), board1, SLOT(setAvaliable(QSet<QPair<int,int> >,bool)));
	QObject::connect(client1, SIGNAL(updateHintMsg(QSet<QPair<int,int> >,bool)), board1, SLOT(showHint(QSet<QPair<int,int> >,bool)));
	QObject::connect(board1, SIGNAL(chosenButton(QPair<int,int>)), client1, SLOT(chooseBtn(QPair<int,int>)));
	QObject::connect(client1, SIGNAL(setChosenMsg(QVector<QPair<int,int> >,bool)), board1, SLOT(setChosen(QVector<QPair<int,int> >,bool)));
	QObject::connect(client1, SIGNAL(moveMsg(QVector<QPair<int,int> >)), board1, SLOT(movePieces(QVector<QPair<int,int> >)));
	QObject::connect(client1, SIGNAL(removeMsg(QVector<QPair<int,int> >)), board1, SLOT(removePieces(QVector<QPair<int,int> >)));
	QObject::connect(client1, SIGNAL(upgradeMsg(QPair<int,int>)), board1, SLOT(upgrade(QPair<int,int>)));

	DraughtsBoard* board2 = new DraughtsBoard;
	Client* client2 = new Client;
	Server* server2 = new Server;
	Welcome* wel2 = new Welcome;
	QObject::connect(wel2, SIGNAL(initServerMsg(int)), server2, SLOT(initServer(int)));
	QObject::connect(wel2, SIGNAL(initClientMsg(QHostAddress,int)), client2, SLOT(connectHost(QHostAddress,int)));
	QObject::connect(wel2, SIGNAL(initGameMsg(QString)), client2, SLOT(startGame(QString)));
	QObject::connect(client2, SIGNAL(initDaughtsBoard(QVector<QVector<Piece> >)), board2, SLOT(initWithMat(QVector<QVector<Piece> >)));
	QObject::connect(client2, SIGNAL(updateAvaliableMsg(QSet<QPair<int,int> >,bool)), board2, SLOT(setAvaliable(QSet<QPair<int,int> >,bool)));
	QObject::connect(client2, SIGNAL(updateHintMsg(QSet<QPair<int,int> >,bool)), board2, SLOT(showHint(QSet<QPair<int,int> >,bool)));
	QObject::connect(board2, SIGNAL(chosenButton(QPair<int,int>)), client2, SLOT(chooseBtn(QPair<int,int>)));
	QObject::connect(client2, SIGNAL(setChosenMsg(QVector<QPair<int,int> >,bool)), board2, SLOT(setChosen(QVector<QPair<int,int> >,bool)));
	QObject::connect(client2, SIGNAL(moveMsg(QVector<QPair<int,int> >)), board2, SLOT(movePieces(QVector<QPair<int,int> >)));
	QObject::connect(client2, SIGNAL(removeMsg(QVector<QPair<int,int> >)), board2, SLOT(removePieces(QVector<QPair<int,int> >)));
	QObject::connect(client2, SIGNAL(upgradeMsg(QPair<int,int>)), board2, SLOT(upgrade(QPair<int,int>)));
	board1->show();
	board2->show();
	wel1->show();
	wel2->show();
}

#endif //TESTCOMBINED

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

//	testGame();
//	testNetWork();
//	testPieceBtn();
//	testDraughtsBoard();
	testCombined();

	return app.exec();
}

#endif //TEST
