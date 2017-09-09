#ifndef SIMPLESERVER_H
#define SIMPLESERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include "client/message.h"
#include <QDataStream>

class SimpleServer : public QObject
{
	Q_OBJECT
public:
	explicit SimpleServer(QObject *parent = 0);

signals:

public slots:
	void acceptConnection();
	void recvMsg();

private:
	QTcpServer* listenSocket;
	QTcpSocket* readWriteSocket;
};

#endif // SIMPLESERVER_H
