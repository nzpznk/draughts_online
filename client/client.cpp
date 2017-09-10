#include "client.h"

Client::Client(QObject* parent) : QObject(parent)
{
	this->readWriteSocket = new QTcpSocket;
	game = new Game;
}

Client::~Client()
{
	delete game;
	game = nullptr;
}

void Client::connectHost(const QHostAddress& host, int hostPort)
{
	this->readWriteSocket->connectToHost(host, hostPort);
	connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(receiveMsg()));
}

void Client::startGame(const QString& path)
{
	game->initGame(path);
	emit initDaughtsBoard(game->getMat());
}

void Client::chooseBtn(const QPair<int, int>& posi)
{
	qDebug() << "Client::chooseBtn slot called";
	if(!m_next_btns.contains(posi)) { // 点到的棋子属于m_root_btns
		emit setChosenMsg(m_chosen_btns, false);
		m_chosen_btns.clear();
	}
	m_chosen_btns.push_back(posi);
	updateHints();
	updateNextBtns();
	if(m_chosen_btns.size() == m_all_avaliable_routes[m_chosen_btns[0]][0].size()) {
		qDebug() << "emit Client::moveMsg()";
		emit movePieces(m_chosen_btns);
		sendMsg(Message("move", m_chosen_btns));
		emit updateHintMsg(m_hint_btns, false);
		m_hint_btns.clear();
		emit updateAvaliableMsg(m_root_btns + m_next_btns, false);
		m_root_btns.clear();
		m_next_btns.clear();
		m_chosen_btns.clear();
	}
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
		solveMsg(msg);
	}
}

void Client::movePieces(const QVector<QPair<int, int> > pieces)
{
	QVector< QPair<int, int> > toRemove;
	for(int i = 0; i < pieces.size() - 1; ++i) {
		auto tmp = game->move(pieces[i], pieces[i + 1]);
		qDebug() << "Client::movePieces: movepath" << pieces;
		if(tmp.first == -1 && tmp.second == -1) continue;
		toRemove.push_back(tmp);
	}
	emit moveMsg(pieces);
	if(game->upgrade(pieces[pieces.size()-1])) {
		qDebug() << "upgrading" << pieces[pieces.size()-1];
		emit upgradeMsg(pieces[pieces.size()-1]);
	}
	emit removePieces(toRemove);
}

void Client::removePieces(const QVector<QPair<int, int> > pieces)
{
	game->remove(pieces);
	emit removeMsg(pieces);
}

void Client::solveMsg(const Message& msg)
{
	if(msg.str == "move") {
		emit movePieces(msg.vec);
		m_all_avaliable_routes = game->getAllMovablePieces(isBlack);
		foreach (auto key, m_all_avaliable_routes.keys()) {
			m_root_btns.insert(key);
		}
		emit updateAvaliableMsg(m_root_btns, true);
	} else if (msg.str == "finish") { // if the other one finished, it's turn
		m_all_avaliable_routes = game->getAllMovablePieces(isBlack);
		emit updateAvaliableMsg(m_root_btns, false);
		m_root_btns.clear();
		QPair<int, int> key;
		foreach (key, m_all_avaliable_routes.keys()) {
			m_root_btns.insert(key);
		}
		emit updateAvaliableMsg(m_root_btns, true);
		//////////// remove hints and avaliable btns
	} else if (msg.str == "black") {
		isBlack = true;
		m_all_avaliable_routes = game->getAllMovablePieces(isBlack);
		foreach (auto key, m_all_avaliable_routes.keys()) {
			m_root_btns.insert(key);
		}
		emit updateAvaliableMsg(m_root_btns, true);
	} else if (msg.str == "white") {
		isBlack = false;
//		m_all_avaliable_routes = game->getAllMovablePieces(isBlack);
//		foreach (auto key, m_all_avaliable_routes.keys()) {
//			m_root_btns.insert(key);
//		}
		emit updateAvaliableMsg(m_root_btns, true);
	} else if (msg.str == "win") {
		emit showWinMsg(true);
	} else if (msg.str == "lose") {
		emit showWinMsg(false);
	}
}

void Client::updateHints()
{
	if(!m_chosen_btns.size()) return;
	QSet< QPair<int, int> > newhints;
	auto routes = m_all_avaliable_routes[m_chosen_btns[0]];
	for(auto route : routes) {
		bool flag = false;
		for(int i = 0; i < m_chosen_btns.size(); ++i) {
			if(route[i] != m_chosen_btns[i]) {
				flag = true;
				break;
			}
		}
		if(flag) continue;
		for(int i = m_chosen_btns.size(); i < route.size(); ++i) {
			newhints.insert(route[i]);
		}
	}
	emit updateHintMsg(newhints - m_hint_btns, true); // 新加入的hint
	emit updateHintMsg(m_hint_btns - newhints, false); // 移除的hint
	m_hint_btns = newhints;
}

void Client::updateNextBtns()
{
	if(!m_chosen_btns.size()) return;
	QSet< QPair<int, int> > new_next_btns;
	auto routes = m_all_avaliable_routes[m_chosen_btns[0]];
	for(auto route : routes) {
		bool flag = false;
		for(int i = 0; i < m_chosen_btns.size(); ++i) {
			if(route[i] != m_chosen_btns[i]) {
				flag = true;
				break;
			}
		}
		if(flag) continue;
		if(m_chosen_btns.size() < route.size()) {
			new_next_btns.insert(route[m_chosen_btns.size()]);
		}
	}
	emit updateAvaliableMsg(m_next_btns - new_next_btns, false);  // 移除的可点击棋子
	emit updateAvaliableMsg(new_next_btns - m_next_btns, true); // 新加入的可点击棋子
//	emit updateHintMsg(m_next_btns - new_next_btns, false);
	m_next_btns = new_next_btns;
}

void Client::sendMsg(const Message& msg)
{
	QDataStream s(readWriteSocket);
	s << msg;
}

void Client::on_pushButton_clicked()
{
	QString str;
	sendMsg(Message(str, QVector< QPair<int, int> >({QPair<int, int>(2, 3), QPair<int, int>(1, 5)})));
}
