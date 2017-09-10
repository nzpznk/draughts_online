#include "piecebtn.h"

PieceBtn::PieceBtn(QWidget* parent): \
	QLabel(parent),
	m_clickable(false)
{
	m_borderStyle = "border: 2px solid rgba(255, 255, 0, 0);";
	m_backgroundStyle = "background-color: none;";
	updateStyle();
}

PieceBtn::~PieceBtn()
{

}

void PieceBtn::setClickable(bool clickable)
{
	m_clickable = clickable;
}

void PieceBtn::setIcon(Piece p)
{
	setPixmap(Icons::getIcon(p));
}

void PieceBtn::showAvaliable(bool avaliable)
{
	if(avaliable) {
		m_borderStyle = "border: 2px solid rgb(255, 255, 0);";
	} else {
		m_borderStyle = "border: 2px solid rgba(255, 255, 0, 0);";
	}
	updateStyle();
}

void PieceBtn::showChosen(bool chosen)
{
	if(chosen) {
		m_backgroundStyle = "background-color: rgba(0, 0, 255, 0.4);";
	} else {
		m_backgroundStyle = "background-color: none;";
	}
	updateStyle();
}

void PieceBtn::updateStyle()
{
	setStyleSheet(m_backgroundStyle + m_borderStyle);
}

void PieceBtn::mousePressEvent(QMouseEvent*)
{

}

void PieceBtn::mouseReleaseEvent(QMouseEvent* ev)
{
	if(!m_clickable) return;
	if( ev->x() < 0 || ev->x() > size().width() || \
		ev->y() < 0 || ev->y() > size().height() )
	{
		return;
	}
	qDebug() << "mouseReleased";
	emit clicked();
}
