#include "draughtsboard.h"
#include "ui_draughtsboard.h"

DraughtsBoard::DraughtsBoard(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DraughtsBoard),
	m_clicksound(this)
{
	ui->setupUi(this);
	m_soundOn = true;
	ui->sound->setChecked(true);
	m_clicksound.setSource(QUrl::fromLocalFile(":/sound/resources/settle.wav"));
	m_clicksound.setVolume(1.0f);
}

DraughtsBoard::~DraughtsBoard()
{
	delete ui;
}

void DraughtsBoard::initWithMat(const QVector< QVector<Piece> >& mat)
{
	if(mat.size() != 10 || mat[0].size() != 10) {
		qDebug() << "error when initWithMat";
		return;
	}
	PieceBtn* btn = nullptr;
	for(int i = 0; i < 10; ++i) {
		for(int j = 0; j < 10; ++j) {
			btn = new PieceBtn(this);
			m_btns[i][j] = btn;
			btn->setIcon(mat[i][j]);
			ui->boardLayout->addWidget(btn, i, j);
			if( (i + j) & 1 ) {
				connect(btn, &PieceBtn::clicked, [=]() {
					btnClicked(QPair<int, int>(i, j));
					if(m_soundOn) m_clicksound.play();
				});
			}
		}
	}
}

void DraughtsBoard::setAvaliable(const QSet<QPair<int, int> >& btns, bool avaliable)
{
	for(QPair<int, int> posi : btns) {
		m_btns[posi.first][posi.second]->setClickable(avaliable);
		m_btns[posi.first][posi.second]->showAvaliable(avaliable);
	}
}

void DraughtsBoard::showHint(const QSet<QPair<int, int> >& btns, bool hint)
{
	Piece val = hint ? Piece::HINT : Piece::NONE;
	for(QPair<int, int> posi : btns) {
		m_btns[posi.first][posi.second]->setIcon(val);
	}
}

void DraughtsBoard::setChosen(const QVector<QPair<int, int> >& vec, bool chosen)
{
	for(auto p : vec) {
		m_btns[p.first][p.second]->showChosen(chosen);
	}
}

void DraughtsBoard::movePieces(const QVector<QPair<int, int> >& vec)
{
	for(int i = 0; i < vec.size() - 1; ++i) {
		m_btns[vec[i].first][vec[i].second]->showChosen(false);
		m_btns[vec[i].first][vec[i].second]->showAvaliable(false);
	}
	m_btns[vec[vec.size()-1].first][vec[vec.size()-1].second]->setIcon(m_btns[vec[0].first][vec[0].second]->getCategory());
	m_btns[vec[0].first][vec[0].second]->setIcon(Piece::NONE);
}

void DraughtsBoard::removePieces(const QVector<QPair<int, int> >& vec)
{
	for(auto p : vec) {
		m_btns[p.first][p.second]->setIcon(Piece::NONE);
		m_btns[p.first][p.second]->showChosen(false);
		m_btns[p.first][p.second]->showAvaliable(false);
		m_btns[p.first][p.second]->setClickable(false);
	}
}

void DraughtsBoard::upgrade(const QPair<int, int>& p)
{
	if(m_btns[p.first][p.second]->getCategory() == Piece::WHITE) {
		m_btns[p.first][p.second]->setIcon(Piece::WKING);
	} else if (m_btns[p.first][p.second]->getCategory() == Piece::BLACK) {
		m_btns[p.first][p.second]->setIcon(Piece::BKING);
	} else {
		qDebug() << "upgrade error";
	}
}

void DraughtsBoard::showDrawRequest()
{
	int ret = QMessageBox::warning(this, QStringLiteral("对方请求和棋"),
								   QStringLiteral("你同意吗"),
								   QMessageBox::Yes
								   | QMessageBox::No);
	if(ret & QMessageBox::Yes) {
		emit drawAnswerMsg(true);
		qDebug() << "request draw";
		this->close();
	} else {
		emit drawAnswerMsg(false);
		qDebug() << "cancel request draw";
	}
}

void DraughtsBoard::showDrawAnswer(bool ok)
{
	if(ok) {
		QMessageBox::information( this, QStringLiteral("和棋"), \
										QStringLiteral("对方接受了你的请求"),\
										QMessageBox::Cancel);
		this->close();
	} else {
		QMessageBox::information( this, QStringLiteral("和棋"), \
										QStringLiteral("对方拒绝了你的请求"),\
										QMessageBox::Cancel);
	}
}

void DraughtsBoard::showEasyWin()
{
	QMessageBox::information( this, QStringLiteral("获胜"), \
									QStringLiteral("对方投降, 你已获胜"),\
							  QMessageBox::Cancel);
	this->close();
}

void DraughtsBoard::showIsWinner(bool isWinner)
{
	if(isWinner) {
		QMessageBox::information( this, QStringLiteral("获胜"), \
										QStringLiteral("恭喜, 你已获胜"),\
										QMessageBox::Cancel);
	} else {
		QMessageBox::information( this, QStringLiteral("失败"), \
										QStringLiteral("再接再厉"),\
										QMessageBox::Cancel);
	}
	this->close();
}

void DraughtsBoard::btnClicked(const QPair<int, int>& posi)
{
	qDebug() << "button" << posi << "is chosen";
	m_btns[posi.first][posi.second]->showChosen(true);
	emit chosenButton(posi);
}


void DraughtsBoard::on_sound_toggled(bool soundOn)
{
	m_soundOn = soundOn;
}

void DraughtsBoard::on_draw_request_triggered()
{
	int ret = QMessageBox::warning(this, QStringLiteral("请求和棋"),
								   QStringLiteral("你确定要和棋吗"),
								   QMessageBox::Ok
								   | QMessageBox::Cancel);
	if(ret & QMessageBox::Ok) {
		emit drawMsg();
		qDebug() << "request draw";
	} else {
		qDebug() << "cancel request draw";
	}
}

void DraughtsBoard::on_giveup_triggered()
{
	int ret = QMessageBox::warning(this, QStringLiteral("认输"),
								   QStringLiteral("你确定要认输吗"),
								   QMessageBox::Ok
								   | QMessageBox::Cancel);
	if(ret & QMessageBox::Ok) {
		emit loseMsg();
		qDebug() << "request lose";
	} else {
		qDebug() << "cancel request lose";
	}
	this->close();
}
