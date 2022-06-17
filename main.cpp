#include <QApplication>
#include <QSettings>
#include "sockettest.h"
#include "mainwindow.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	app.setOrganizationName("miraya");
	app.setOrganizationDomain("github.com/MirayaProject");
	app.setApplicationName("bot");
	MainWindow mw;
	mw.show();
	return app.exec();
}
