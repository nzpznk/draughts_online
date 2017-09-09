#ifndef ICONS_H
#define ICONS_H

#include "logic/piece.h"
#include <QPixmap>
#include <QDebug>

class Icons
{
public:
	static QPixmap& getIcon(Piece p);
private:
	Icons();
	QPixmap m_white_icon;
	QPixmap m_black_icon;
	QPixmap m_wking_icon;
	QPixmap m_bking_icon;
	QPixmap m_hint_icon;
	static Icons* instance;
};

#endif // ICONS_H
