﻿#include "logic/game.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <iostream>

Game::Game()
{
}

void Game::initGame(const QString& path)
{
	QFile fl(path);
	if(!fl.open(QIODevice::ReadOnly | QIODevice::Text)) {
		std::cout << "cannot open file" << std::endl;
		return;
	}
	int tmp;
	QTextStream tr(&fl);
	for(int i = 0; i < 10; ++i) {
		for(int j = 0; j < 10; ++j) {
			tr >> tmp;
			mat[i][j] = Piece(tmp);
		}
	}
//	for(int i = 0; i < 10; ++i) {
//		for(int j = 0; j < 10; ++j) {
//			std::cout << mat[i][j];
//		}
//		std::cout << std::endl;
//	}
}

void Game::move(int a, int b, bool isBlack)
{

}

QVector< QVector< QPair<int, int> > > Game::getAvaliableRoute(const QPair<int, int>& posi)
{
	QVector< QVector< QVector< QPair<int, int> > > > dfsAns;
	for(int i = 0; i < 4; ++i) {
		QPair<int, int> nposi(posi.first + dx[i], posi.second + dy[i]);
		if(!valid(nposi)) continue;
		if(	(piece(posi) == Piece::WHITE && (piece(nposi) == Piece::BLACK || piece(nposi) == Piece::BKING)) || \
			(piece(posi) == Piece::BLACK && (piece(nposi) == Piece::WHITE || piece(nposi) == Piece::WKING)) )
		{
			// 检查下一位是否是NONE，如果是就将posi处换为NONE，新的posi处换为原posi，递归得到以posi开始的路径，将posi和递归的posi还原
			QPair<int, int> nextPosi(nposi.first + dx[i], nposi.second + dy[i]);
			if(!valid(nextPosi)) {
				continue;
			} else if(piece(nextPosi) == Piece::NONE) {
				piece(nextPosi) = piece(posi);
				piece(posi) = Piece::NONE;
				Piece tmp = piece(nposi);
				piece(nposi) = Piece::VISITED;
				dfsAns.push_back(getAvaliableRoute(nextPosi));
				piece(posi) = piece(nextPosi);
				piece(nposi) = tmp;
				piece(nextPosi) = Piece::NONE;
			} else {
				continue;
			}
		}
		else if (piece(posi) == Piece::WKING || piece(posi) == Piece::BKING)
		{
			while(valid(nposi) && piece(nposi) == Piece::NONE) { // 尝试走到棋子前一个位置
				nposi.first += dx[i];
				nposi.second += dy[i];
			}
			if(!valid(nposi)) continue;
			if( (piece(posi) == Piece::WKING && (piece(nposi) == Piece::BLACK || piece(nposi) == Piece::BKING)) || \
				(piece(posi) == Piece::BKING && (piece(nposi) == Piece::WHITE || piece(nposi) == Piece::WKING)) )
			{
				QPair<int, int> nextPosi(nposi.first + dx[i], nposi.second + dy[i]);
				if(!valid(nextPosi)) {
					continue;
				} else if(piece(nextPosi) == Piece::NONE) {
					while(valid(nextPosi) && piece(nextPosi) == Piece::NONE) {
						piece(nextPosi) = piece(posi);
						piece(posi) = Piece::NONE;
						Piece tmp = piece(nposi);
						piece(nposi) = Piece::VISITED;
						dfsAns.push_back(getAvaliableRoute(nextPosi));
						piece(posi) = piece(nextPosi);
						piece(nposi) = tmp;
						piece(nextPosi) = Piece::NONE;
						nextPosi.first += dx[i];
						nextPosi.second += dy[i];
					}
				} else {
					continue;
				}
			} else { // piece(nposi) 与piece(posi) 颜色相同不能被吃，或者处于visited状态不能越过
				continue;
			}
		}
		else
		{ // 不能跳吃或已经屏蔽
			continue;
		}
	}
	// insert the posi to each route before return
	int maxlen = 0;
	QVector< QVector< QPair<int, int> > > ans;
	for(auto preAns : dfsAns) {
		if(!preAns.size()) continue; // 这个方向上不能吃子，不能走
		if(preAns[0].size() > maxlen) {
			maxlen = preAns[0].size();
		}
	}
	if(maxlen == 0) {
		ans.push_back(QVector< QPair<int, int> >({posi}));
		return ans;
	}
	for(auto preAns : dfsAns) {
		if(!preAns.size() || preAns[0].size() < maxlen) continue;
		for(QVector< QPair<int, int> > route : preAns) {
			ans.push_back(QVector< QPair<int, int> >({posi}) + route);
		}
	}
	return ans;
}

bool Game::valid(const QPair<int, int>& posi)
{
	if(posi.first > 9 || posi.second > 9 || posi.first < 0 || posi.second < 0) return false;
	else return true;
}

Piece& Game::piece(const QPair<int, int>& posi)
{
	return mat[posi.first][posi.second];
}
