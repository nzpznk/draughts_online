#include "simpleserver.h"

SimpleServer::SimpleServer(QObject *parent) : QObject(parent)
{
	listenSocket = new QTcpServer;
	listenSocket->listen(QHostAddress::Any, 8321);
	connect(this->listenSocket, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void SimpleServer::acceptConnection()
{
	readWriteSocket = listenSocket->nextPendingConnection();
	connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
}

void SimpleServer::recvMsg()
{
	qDebug() << readWriteSocket->peerAddress();
	Message msg;
	QDataStream s(readWriteSocket);
	while(!s.atEnd()) {
		s.startTransaction(); // 来自另一个设备，防止传输未完成而保存流的状态
		s >> msg;
		if(!s.commitTransaction()) return; // 如果读入不彻底，直接恢复流的状态并返回
		qDebug() << "simple server received:" << msg.str << msg.vec;
	}
}
