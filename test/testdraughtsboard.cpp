#include "testdraughtsboard.h"
#include "ui_testdraughtsboard.h"

TestDraughtsBoard::TestDraughtsBoard(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TestDraughtsBoard)
{
	ui->setupUi(this);
}

TestDraughtsBoard::~TestDraughtsBoard()
{
	delete ui;
}

void TestDraughtsBoard::on_pushButton_clicked()
{
	QFile f("./standard.txt");
//	QFile f("./normal.txt");
//	QFile f("./king.txt");
	if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "file cannot open";
		return;
	}
	QTextStream stream(&f);
	int tmp;
	for(int i = 0; i < 10; ++i) {
		QVector<Piece> row;
		for(int j = 0; j < 10; ++j) {
			stream >> tmp;
			row.push_back(Piece(tmp));
		}
		mat.push_back(row);
	}
	emit showPieceMsg(mat);
}
