#include <QApplication>
#include <QIcon>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	app.setOrganizationName("miraya");
	app.setOrganizationDomain("github.com/MirayaProject");
	app.setApplicationName("bot");
	app.setApplicationVersion("1.2.0");
	#ifdef Q_OS_LINUX
		app.setWindowIcon(QIcon(":/resources/logo/logo.png"));
	#endif
	MainWindow mw;
	mw.show();
	return app.exec();
}
