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
