#include <QApplication>
#include <QObject>
#include <QDebug>
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

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

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
	QObject::connect(board1, SIGNAL(drawMsg()), client1, SLOT(askForDraw()));
	QObject::connect(client1, SIGNAL(drawRequestMsg()), board1, SLOT(showDrawRequest()));
	QObject::connect(board1, SIGNAL(drawAnswerMsg(bool)), client1, SLOT(sendDrawAnswer(bool)));
	QObject::connect(client1, SIGNAL(drawAnswer(bool)), board1, SLOT(showDrawAnswer(bool)));
	QObject::connect(board1, SIGNAL(loseMsg()), client1, SLOT(sendLoseRequest()));
	QObject::connect(client1, SIGNAL(showEasyWin()), board1, SLOT(showEasyWin()));
	QObject::connect(client1, SIGNAL(showWinMsg(bool)), board1, SLOT(showIsWinner(bool)));
	QObject::connect(wel1, SIGNAL(showGameBoard()), board1, SLOT(show()));
	wel1->show();

	return app.exec();
}
