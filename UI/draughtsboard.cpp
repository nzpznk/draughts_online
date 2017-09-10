#include "draughtsboard.h"
#include "ui_draughtsboard.h"

DraughtsBoard::DraughtsBoard(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DraughtsBoard)
{
	ui->setupUi(this);
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

void DraughtsBoard::btnClicked(const QPair<int, int>& posi)
{
	qDebug() << "button" << posi << "is chosen";
	m_btns[posi.first][posi.second]->showChosen(true);
	emit chosenButton(posi);
}
