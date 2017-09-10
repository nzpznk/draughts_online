#include "icons.h"

Icons* Icons::instance = nullptr;

QPixmap& Icons::getIcon(Piece p)
{
	if(!instance) {
		instance = new Icons;
	}
	switch(p) {
	case Piece::NONE: return instance->m_none_icon;
	case Piece::WHITE: return instance->m_white_icon;
	case Piece::BLACK: return instance->m_black_icon;
	case Piece::WKING: return instance->m_wking_icon;
	case Piece::BKING: return instance->m_bking_icon;
	case Piece::HINT: return instance->m_hint_icon;
	default:
		qDebug() << "error in Icons::getIcon()";
		return instance->m_hint_icon;
	}
}

Icons::Icons()
{
	m_white_icon = QPixmap(":/picture/resources/white.png");
	m_black_icon = QPixmap(":/picture/resources/black.png");
	m_wking_icon = QPixmap(":/picture/resources/wking.png");
	m_bking_icon = QPixmap(":/picture/resources/bking.png");
	m_hint_icon = QPixmap(":/picture/resources/hint.png");
}
