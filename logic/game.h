
#include <QVector>
#include "piece.h"

class Game {
public:
	Game();
	void initGame(const QString& path); // init to standard position
	void move(int a, int b, bool isBlack); // move from position a to position b
	// get all possiable routes with jump. if size == 0, the piece can only move.
	QVector< QVector< QPair<int, int> > > getAvaliableRoute(const QPair<int, int>& posi); // test passed

private:
	bool valid(const QPair<int, int>& posi);
	Piece& piece(const QPair<int, int>& posi);
private:
	Piece mat[10][10];
	int dx[4] = {-1, -1, 1, 1};
	int dy[4] = {-1, 1, -1, 1};
};
