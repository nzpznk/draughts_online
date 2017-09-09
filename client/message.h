#ifndef MESSAGE_H
#define MESSAGE_H

/*
 * Message::str: "move"(移动), "remove"(移除)", win"(获胜), "lose"(失败)
 */

#include <QDataStream>

struct Message {
	Message() {}
	Message(const QString& s, const QVector< QPair<int, int> >& v) : \
		str(s), vec(v) {}
	QString str;
	QVector< QPair<int, int> > vec;
};

QDataStream& operator<< (QDataStream& out, const Message& msg);
QDataStream& operator>> (QDataStream& in, Message& msg);

#endif // MESSAGE_H
