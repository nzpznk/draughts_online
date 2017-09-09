#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include "client/message.h"

class Client : QObject
{

public:
	explicit Client();
	~Client();
	void connectHost(int port);

private:
	void receiveMsg();
//	void choose(const QPair<int, int>& p);

	void on_pushButton_clicked();

public:
	//if cannot move, send win/lose message
//	QPair<int, int> movePiece(const QPair<int, int>& st, const QPair<int, int>& ed);
//	void removePiece(const QVector< QPair<int, int> >& pieces);
//	void showGame();
	void sendMsg(const Message& msg);
//	void updateRoutes();

private:
//	Game* game;
//	QMap< QPair<int, int>, QVector< QVector< QPair<int, int> > > > routes;
//	bool isBlack;
	bool isHost;
	QTcpSocket* readWriteSocket;
};

#endif // CLIENT_H
