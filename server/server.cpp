#include "server.h"

Server::Server(QObject *parent) : QObject(parent), m_num_tables(5)
{
	for(int i = 0; i < m_num_tables; ++i) {
		m_tables.insert(i);
	}
}

void Server::initServer(int port)
{
	listenSocket = new QTcpServer;
	listenSocket->listen(QHostAddress::Any, port);
	connect(this->listenSocket, &QTcpServer::newConnection, [&]() {
		QTcpSocket* socket = listenSocket->nextPendingConnection();
		if(m_waiting_tables.size()) {
			int t = *m_waiting_tables.constBegin();
			player2.insert(t, socket);
			m_waiting_tables.remove(t);
			gameStart(t);
			return;
		}
		if(!m_tables.size()) {
			qDebug() << "connection full";
			delete socket;
			socket = nullptr;
			return;
		}
		int x = *m_tables.constBegin();
		player1.insert(x, socket);
		m_tables.remove(x);
		m_waiting_tables.insert(x);
	});
}

void Server::gameStart(int table)
{
	Message info;
	QTcpSocket* sock1 = player1[table];
	QTcpSocket* sock2 = player2[table];
	QDataStream s1(sock1);
	QDataStream s2(sock2);
	info.str = "white";
	s1 << info;
	info.str = "black";
	s2 << info;
	connect(sock1, &QTcpSocket::readyRead, [=]() {
		Message msg = getMsg(sock1);
		if(msg.str == "finish") {
			removeConnection(table);
			return;
		}
		sendTo(sock2, msg);
	});
	connect(sock2, &QTcpSocket::readyRead, [=]() {
		Message msg = getMsg(sock1);
		if(msg.str == "finish") {
			removeConnection(table);
			return;
		}
		sendTo(sock2, msg);
	});
}

Message Server::getMsg(QTcpSocket* socket)
{
	Message ans;
	QDataStream s(socket);
	s >> ans;
//	if(ans.str == "finish") {
//		delete socket;
//		socket = nullptr;
//	}
	return ans;
}

void Server::removeConnection(int table)
{
	delete player1[table];
	player1.remove(table);
	delete player2[table];
	player2.remove(table);
	m_tables.insert(table);
}

void Server::sendTo(QTcpSocket* socket, const Message& info)
{
	QDataStream s(socket);
	s << info;
//	if(info.str == "finish") {

//	}
}
