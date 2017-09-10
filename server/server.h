#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include "client/message.h"

class Server : public QObject
{
	Q_OBJECT
public:
	explicit Server(QObject *parent = 0);

public slots:
	void initServer(int port);

private:
	void gameStart(int table);
	Message getMsg(QTcpSocket* socket);
	void removeConnection(int table);
	void sendTo(QTcpSocket* socket, const Message& info);

private:
	int m_num_tables;
	QSet<int> m_tables;
	QSet<int> m_waiting_tables;
	QMap<int, QTcpSocket*> player1;
	QMap<int, QTcpSocket*> player2;
	QTcpServer* listenSocket;
};

#endif // SERVER_H
