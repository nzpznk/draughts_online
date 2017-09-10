#ifndef DRAUGHTSBOARD_H
#define DRAUGHTSBOARD_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QSoundEffect>
#include <QUrl>
#include <QMessageBox>
#include "UI/piecebtn.h"
#include "logic/piece.h"

namespace Ui {
class DraughtsBoard;
}

class DraughtsBoard : public QMainWindow
{
	Q_OBJECT

public:
	explicit DraughtsBoard(QWidget *parent = 0);
	~DraughtsBoard();

signals:
	void chosenButton(const QPair<int, int> chosenbtn);
	void drawMsg();
	void loseMsg();
	void drawAnswerMsg(bool ok);

public slots:
	void initWithMat(const QVector< QVector<Piece> >& mat);
	void setAvaliable(const QSet< QPair<int, int> >& btns, bool avaliable);
	void showHint(const QSet< QPair<int, int> >& btns, bool hint);
	void setChosen(const QVector< QPair<int, int> >& vec, bool chosen);
	void movePieces(const QVector< QPair<int, int> >& vec);
	void removePieces(const QVector< QPair<int, int> >& vec);
	void upgrade(const QPair<int, int>& p);
	void showDrawRequest();
	void showDrawAnswer(bool ok);
	void showEasyWin();
	void showIsWinner(bool isWinner);

private slots:
	void on_sound_toggled(bool soundOn);

	void on_draw_request_triggered();

	void on_giveup_triggered();

private:
	void btnClicked(const QPair<int, int>& posi);

private:
	bool m_soundOn;
	QSoundEffect m_clicksound;
	PieceBtn* m_btns[10][10];
	Ui::DraughtsBoard *ui;
};

#endif // DRAUGHTSBOARD_H
