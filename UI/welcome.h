#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>
#include <QDebug>
#include <QNetworkInterface>
#include <QHostAddress>

namespace Ui {
class Welcome;
}

class Welcome : public QDialog
{
	Q_OBJECT

signals:
	void initServerMsg(int port);
	void initClientMsg(const QHostAddress& hostIp, int hostPort);
	void initGameMsg(const QString& path);

public:
	explicit Welcome(QWidget *parent = 0);
	~Welcome();

private slots:
	void on_checkBox_toggled(bool checked);
	void getSelfIp();
	void startConnection();

private:
	bool isServer;
	Ui::Welcome *ui;
};

#endif // WELCOME_H
