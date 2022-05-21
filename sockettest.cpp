#include "sockettest.h"

SocketTest::SocketTest(
	const QUrl &url,
	QObject *parent
) : QObject(parent) {
	connect(&socket, &QWebSocket::connected, this, &SocketTest::onConnected);
	connect(&socket, &QWebSocket::textMessageReceived, this, &SocketTest::onTextMessageReceived);
	connect(&socket, &QWebSocket::disconnected, this, &SocketTest::onDisconnected);
	socket.open(QUrl(url));
}

void SocketTest::disconnect() {
	socket.disconnect();
}


void SocketTest::onConnected() {
	qDebug() << "Connected!";
}


void SocketTest::onTextMessageReceived(QString message){
	qDebug() << "Message received: " << message;
}

void SocketTest::onDisconnected(){
	qDebug() << "Disconnected!";
}