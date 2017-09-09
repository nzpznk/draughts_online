#ifndef DRAUGHTSBOARD_H
#define DRAUGHTSBOARD_H

#include <QMainWindow>

namespace Ui {
class DraughtsBoard;
}

class DraughtsBoard : public QMainWindow
{
	Q_OBJECT

public:
	explicit DraughtsBoard(QWidget *parent = 0);
	~DraughtsBoard();

private:
	Ui::DraughtsBoard *ui;
};

#endif // DRAUGHTSBOARD_H
