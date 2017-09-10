#ifndef DRAUGHTSBOARD_H
#define DRAUGHTSBOARD_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>

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

public slots:
	void initWithMat(const QVector< QVector<Piece> >& mat);
	void setAvaliable(const QSet< QPair<int, int> >& btns, bool avaliable);
	void showHint(const QSet< QPair<int, int> >& btns, bool hint);
	void setChosen(const QVector< QPair<int, int> >& vec, bool chosen);

private:
	void btnClicked(const QPair<int, int>& posi);

private:
	PieceBtn* m_btns[10][10];
	Ui::DraughtsBoard *ui;
};

#endif // DRAUGHTSBOARD_H
