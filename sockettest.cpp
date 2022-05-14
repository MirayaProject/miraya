#include "sockettest.h"

SocketTest::SocketTest(QObject *parent) : QObject(parent){
}

void SocketTest::connect() {
	socket = new QTcpSocket(this);
	socket->connectToHost("127.0.0.1", 24050); // TODO: add port and hostname as parameters

	if (socket->waitForConnected(1000)) {
		qDebug() << "Connected!";

		qDebug() << "Gathering data..." << socket->bytesAvailable();
		qDebug() << socket->readAll();

		qDebug() << "Closing socket...";

	} else {
		qDebug() << "Not connected!";
		return;
	}
	socket->close();
}