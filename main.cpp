
#include <QApplication>
#include "UI/welcome.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);
	Welcome* welcomeDialog = new Welcome;
	welcomeDialog->show();

	return app.exec();
}
