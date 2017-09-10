#include "testpiecebtn.h"
#include "ui_testpiecebtn.h"

TestPieceBtn::TestPieceBtn(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::testPieceBtn)
{
	ui->setupUi(this);
	ui->label->setClickable(true);
	connect(ui->label, SIGNAL(clicked()), this, SLOT(when_label_clicked()));
}

TestPieceBtn::~TestPieceBtn()
{
	delete ui;
}

void TestPieceBtn::when_label_clicked()
{
	qDebug() << "label is clicked";
}

void TestPieceBtn::on_checkBox_toggled(bool checked)
{
	if(checked) {
		ui->label->showChosen(true);
	} else {
		ui->label->showChosen(false);
	}
}

void TestPieceBtn::on_checkBox_2_toggled(bool checked)
{
	if(checked) {
		ui->label->showAvaliable(true);
	} else {
		ui->label->showAvaliable(false);
	}
}

void TestPieceBtn::on_pushButton_clicked()
{
	ui->label->setIcon(Piece::WHITE);
}

void TestPieceBtn::on_pushButton_2_clicked()
{
	ui->label->setIcon(Piece::BLACK);
}

void TestPieceBtn::on_pushButton_3_clicked()
{
	ui->label->setIcon(Piece::WKING);
}

void TestPieceBtn::on_pushButton_4_clicked()
{
	ui->label->setIcon(Piece::BKING);
}

void TestPieceBtn::on_pushButton_5_clicked()
{
	ui->label->setIcon(Piece::HINT);
}

void TestPieceBtn::on_pushButton_6_clicked()
{
	ui->label->setIcon(Piece::NONE);
}
