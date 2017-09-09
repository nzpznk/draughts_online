#ifndef PIECEBTN_H
#define PIECEBTN_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include "logic/piece.h"
#include "UI/icons.h"

class PieceBtn : public QLabel
{
	Q_OBJECT

signals:
	void clicked();

public:
	PieceBtn(QWidget* parent = 0);
	~PieceBtn();
	void setClickable(bool clickable);
	void setIcon(Piece p);
	void showAvaliable(bool avaliable);
	void showChosen(bool chosen);

private:
	void updateStyle();
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent* ev);

private:
	QString m_borderStyle;
	QString m_backgroundStyle;
	bool m_clickable;

};

#endif // PIECEBTN_H
