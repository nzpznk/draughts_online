#ifndef TESTPIECEBTN_H
#define TESTPIECEBTN_H

#include <QDialog>
#include <QDebug>
#include "logic/piece.h"

namespace Ui {
class testPieceBtn;
}

class TestPieceBtn : public QDialog
{
	Q_OBJECT

public:
	explicit TestPieceBtn(QWidget *parent = 0);
	~TestPieceBtn();

private slots:
	void when_label_clicked();

	void on_checkBox_toggled(bool checked);

	void on_checkBox_2_toggled(bool checked);

	void on_pushButton_clicked();

	void on_pushButton_2_clicked();

	void on_pushButton_3_clicked();

	void on_pushButton_4_clicked();

	void on_pushButton_5_clicked();

private:
	Ui::testPieceBtn *ui;
};

#endif // TESTPIECEBTN_H
