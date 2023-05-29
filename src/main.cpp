#include <QApplication>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	app.setOrganizationName("miraya");
	app.setOrganizationDomain("github.com/MirayaProject");
	app.setApplicationName("bot");
	app.setApplicationVersion("1.2.0-alpha.2");
	MainWindow mw;
	mw.show();
	return app.exec();
}
