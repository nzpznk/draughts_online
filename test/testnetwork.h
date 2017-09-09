#ifndef TESTNETWORK_H
#define TESTNETWORK_H

//#include "message.h"
#include "client/client.h"
#include "test/simpleserver.h"


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


void testNetWork() {
	Client* client = new Client;
	SimpleServer* server = new SimpleServer;
//	client->show();
	client->connectHost(8321);
}

#endif // TESTNETWORK_H
