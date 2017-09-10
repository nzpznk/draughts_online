#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QSet>
#include <QMap>
#include <QVector>
#include <QPair>
#include "client/message.h"
#include "logic/game.h"

class Client : QObject
{

signals:
	void setChosenMsg(const QVector< QPair<int, int> >& vec, bool choose);
	void updateAvaliableMsg(const QSet< QPair<int, int> >& btns, bool avaliable);
	void updateHintMsg(const QSet< QPair<int, int> >& btns, bool hint);
	void moveMsg(const QVector< QPair<int, int> >& btns);
	void removeMsg(const QVector< QPair<int, int> >& btns);/////////////
	void showWinMsg(bool isWinner);

public:
	explicit Client();
	~Client();
	void connectHost(int port);

public slots:
	void chooseBtn(const QPair<int, int>& posi);

private slots:
	void receiveMsg();

private:
	void solveMsg(const Message& msg);
	void updateHints(); //////////////// 依据可选路径和已走路径更新下一步的提示
	void updateNextBtns(); /////////////// 依据可选路径和已走路径更新下一步可选的棋子
	void on_pushButton_clicked();

public:
	//if cannot move, send win/lose message
//	QPair<int, int> movePiece(const QPair<int, int>& st, const QPair<int, int>& ed);
//	void removePiece(const QVector< QPair<int, int> >& pieces);
//	void showGame();
	void sendMsg(const Message& msg);
//	void updateRoutes();

private:
	Game* game;
	QSet< QPair<int, int> > m_next_btns;
	QSet< QPair<int, int> > m_root_btns;
	QSet< QPair<int, int> > m_hint_btns;
	QVector< QPair<int, int> > m_chosen_btns;
	QMap< QPair<int, int>, QVector< QVector< QPair<int, int> > > > m_all_avaliable_routes;
	bool isBlack;
	QTcpSocket* readWriteSocket;
};

#endif // CLIENT_H
