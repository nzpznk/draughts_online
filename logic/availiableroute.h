#ifndef AVAILIABLEROUTE_H
#define AVAILIABLEROUTE_H

#include <QVector>
#include <QPair>

class AvailiableRoute
{
public:
	AvailiableRoute();
	void addRoute(int startP, const QVector<int>& route);
	QVector< QVector<int> > getRoute(int startP);
private:
	QVector< QPair<int, QVector< QVector<int> > > > m_allroutes;
};

#endif // AVAILIABLEROUTE_H
