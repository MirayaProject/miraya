#include <QApplication>
#include <QSettings>
#include "sockettest.h"
#include "mainwindow.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	MainWindow mw;
	QSettings settings("miraya", "bot");
	mw.show();
	return app.exec();
}