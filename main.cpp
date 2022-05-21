#include <QApplication>
#include "sockettest.h"

int main( int argc, char **argv ){
	QApplication app(argc, argv);
	SocketTest client(QUrl(QStringLiteral("ws://localhost:24050/ws")));
	return app.exec();
}