#include "client.h"

Client::Client()
{
	game = new Game;
	game->initGame("./standard.txt");
}

Client::~Client()
{
	delete game;
	game = nullptr;
}

void Client::connectHost(int port)
{
	this->readWriteSocket = new QTcpSocket;
	this->readWriteSocket->connectToHost(QHostAddress("127.0.0.1"), port);
	connect(this->readWriteSocket, SIGNAL(readyRead()), this, SLOT(receiveMsg()));
}

void Client::chooseBtn(const QPair<int, int>& posi)
{
	if(!m_next_btns.contains(posi)) {
		emit setChosenMsg(m_chosen_btns, false);
		m_chosen_btns.clear();
	}
	m_chosen_btns.push_back(posi);
	updateHints();
	updateNextBtns();
	if(m_chosen_btns.size() == m_all_avaliable_routes[m_chosen_btns[0]][0].size()) {
		emit moveMsg(m_chosen_btns);
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

void Client::solveMsg(const Message& msg)
{
	if(msg.str == "move") {
		emit moveMsg(msg.vec);
	} else if (msg.str == "remove") {
		emit removeMsg(msg.vec);
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
	} else if (msg.str == "white") {
		isBlack = false;
	} else if (msg.str == "win") {
		emit showWinMsg(true);
	} else if (msg.str == "lose") {
		emit showWinMsg(false);
	}
}

void Client::updateHints()
{
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
		if(m_chosen_btns.size() < route.size() - 1) {
			new_next_btns.insert(route[m_chosen_btns.size()]);
		}
	}
	emit updateAvaliableMsg(new_next_btns - m_next_btns, true); // 新加入的可点击棋子
	emit updateHintMsg(m_next_btns - new_next_btns, false); // 移除的可点击棋子
	m_next_btns = new_next_btns;
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
