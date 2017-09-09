#include "client.h"

Client::Client()
{
}

Client::~Client()
{
}

void Client::connectHost(int port)
{
	this->readWriteSocket = new QTcpSocket;
	this->readWriteSocket->connectToHost(QHostAddress("127.0.0.1"), port);
	connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(receiveMsg()));
}

void Client::receiveMsg()
{
	Message msg;
	QDataStream s(readWriteSocket);
	while(!s.atEnd()) {
		s.startTransaction();
		s >> msg;
		if(!s.commitTransaction()) return;
		qDebug() << "client received message from server:" << msg.str << msg.vec;
	}
}

void Client::sendMsg(const Message& msg)
{
	QDataStream s(readWriteSocket);
	s << msg;
}

//void Client::choose(const QPair<int, int>& p)
//{
//	if( isBlack && (game->piece(p) == Piece::BLACK || game->piece(p) == Piece::BKING) || \
//		!isBlack && (game->piece(p) == Piece::WHITE || game->piece(p) == Piece::WKING) )
//	{

//	}
//}

//void Client::updateRoutes()
//{
//	this->routes = game->getAllMovablePieces(this->isBlack);
//}

void Client::on_pushButton_clicked()
{
	QString str;
	sendMsg(Message(str, QVector< QPair<int, int> >({QPair<int, int>(2, 3), QPair<int, int>(1, 5)})));
}
