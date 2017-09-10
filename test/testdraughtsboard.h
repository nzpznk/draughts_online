#ifndef TESTDRAUGHTSBOARD_H
#define TESTDRAUGHTSBOARD_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "logic/piece.h"

namespace Ui {
class TestDraughtsBoard;
}

class TestDraughtsBoard : public QDialog
{
	Q_OBJECT

signals:
	void showPieceMsg(const QVector< QVector<Piece> >& mat);

public:
	explicit TestDraughtsBoard(QWidget *parent = 0);
	~TestDraughtsBoard();

private slots:
	void on_pushButton_clicked();

private:
	Ui::TestDraughtsBoard *ui;
	QVector< QVector<Piece> > mat;
};

#endif // TESTDRAUGHTSBOARD_H
