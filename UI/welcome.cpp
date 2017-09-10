#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Welcome),
	isServer(false)
{
	ui->setupUi(this);
	this->setWindowTitle("Draughts");
	on_checkBox_toggled(false);
	getSelfIp();
	connect(ui->refresh_self_ip, SIGNAL(clicked(bool)), this, SLOT(getSelfIp()));
	connect(ui->startbtn, SIGNAL(clicked(bool)), this, SLOT(startConnection()));
}

Welcome::~Welcome()
{
	delete ui;
}

void Welcome::on_checkBox_toggled(bool checked)
{
	qDebug() << "to be server:" << checked;
	if(checked) {
		isServer = true;
		ui->host_ip->setText("127.0.0.1");
		ui->host_ip->setEnabled(false);
	} else {
		isServer = false;
		ui->host_ip->setText("183.172.130.219");
		ui->host_ip->setEnabled(true);
	}
}

void Welcome::getSelfIp()
{
	QString selfIp;
	foreach (auto netInterface, QNetworkInterface::allInterfaces()) {
		auto flags = netInterface.flags();
		if( (bool)(flags & QNetworkInterface::IsRunning) && \
			!(bool)(flags & QNetworkInterface::IsLoopBack))
		{
			foreach (auto address, netInterface.addressEntries()) {
				if(address.ip().protocol() == QAbstractSocket::IPv4Protocol) {
					selfIp = address.ip().toString();
					qDebug() << selfIp;
				}
			}
		}
	}
	ui->self_ip->setText(selfIp);
}

void Welcome::startConnection()
{
	int serverPort = ui->host_port->text().toInt();
	if(isServer) {
		qDebug() << "emit initServerMsg:" << serverPort;
		emit initServerMsg(serverPort);
	}
	qDebug() << "emit initClientMsg:" << QHostAddress(ui->host_ip->text()) << "serverPort:" << serverPort;
	emit initGameMsg("./test.txt");
	emit initClientMsg(QHostAddress(ui->host_ip->text()), serverPort);
	emit showGameBoard();
	this->close();
}
