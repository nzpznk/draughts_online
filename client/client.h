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

class Client : public QObject
{

	Q_OBJECT

signals:
	void initDaughtsBoard(const QVector< QVector<Piece> >& mat);
	void setChosenMsg(const QVector< QPair<int, int> >& vec, bool choose);
	void updateAvaliableMsg(const QSet< QPair<int, int> >& btns, bool avaliable); // connected
	void updateHintMsg(const QSet< QPair<int, int> >& btns, bool hint);
	void moveMsg(const QVector< QPair<int, int> >& btns);
	void removeMsg(const QVector< QPair<int, int> >& btns);
	void showWinMsg(bool isWinner);
	void upgradeMsg(const QPair<int, int>& p);
	void drawRequestMsg(); // connect with gui
	void drawAnswer(bool ok);
	void showEasyWin();

public:
	explicit Client(QObject* parent = 0);
	~Client();

public slots:
	void connectHost(const QHostAddress& host, int hostPort);
	void startGame(const QString& path);
	void chooseBtn(const QPair<int, int>& posi);
	void askForDraw();
	void sendDrawAnswer(bool ok);
	void sendLoseRequest();

private slots:
	void receiveMsg();
	void movePieces(const QVector<QPair<int, int> > pieces);
	void removePieces(const QVector<QPair<int, int> > pieces);

private:
	void solveMsg(const Message& msg);
	void updateHints(); // 依据可选路径和已走路径更新下一步的提示
	void updateNextBtns(); // 依据可选路径和已走路径更新下一步可选的棋子
	void on_pushButton_clicked();

public:
	void sendMsg(const Message& msg);

private:
	Game* game;
	QSet< QPair<int, int> > m_next_btns; // 下一步可以落子的地方(由m_all_avaliable_routes和m_chosen_btns决定)
	QSet< QPair<int, int> > m_root_btns; // 这一轮的起始落子点(每轮更新一次, 由m_all_avaliable_routes决定)
	QSet< QPair<int, int> > m_hint_btns; // 提示的之后落子的路径(由m_all_avaliable_routes和m_chosen_btns决定)
	QVector< QPair<int, int> > m_chosen_btns; // 已经选中的棋子
	QMap< QPair<int, int>, QVector< QVector< QPair<int, int> > > > m_all_avaliable_routes;
	bool isBlack;
	QTcpSocket* readWriteSocket;
};

#endif // CLIENT_H
