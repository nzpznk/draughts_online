
#include <QVector>
#include "piece.h"

class Game {
public:
	Game();

	// init to standard position
	void initGame(const QString& path);

	// move from position st to position ed
	QPair<int, int> move(const QPair<int, int>& st, const QPair<int, int>& ed);

	// get all possiable routes with jump. if size == 0, the piece can only move.
	QVector< QVector< QPair<int, int> > > getAvaliableRoute(const QPair<int, int>& posi); // test passed

	// remove the pieces from the broad
	void remove(const QVector< QPair<int, int> >& pieces);

	void upgrade(const QPair<int, int>& p);

private:
	bool valid(const QPair<int, int>& posi);
	Piece& piece(const QPair<int, int>& posi);

private:
	Piece mat[10][10];
	int dx[4] = {-1, -1, 1, 1};
	int dy[4] = {-1, 1, -1, 1};
};
