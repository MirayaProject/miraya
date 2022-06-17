#include "gosumemoryClient.h"

GosumemoryClient::GosumemoryClient(
	const QUrl &url,
	QObject *parent
) : QObject(parent), url(url)
{
	connect(&socket, &QWebSocket::connected, this, &GosumemoryClient::onConnected);
	connect(&socket, &QWebSocket::textMessageReceived, this, &GosumemoryClient::onMessageReceived);
	connect(&socket, &QWebSocket::disconnected, this, &GosumemoryClient::onDisconnected);
}


void GosumemoryClient::init()
{
	qDebug() << "Connecting to: " << url.toString();
	socket.open(QUrl(url));
}

void GosumemoryClient::restart()
{
	socket.close();
	init();
}

void GosumemoryClient::onConnected()
{
	qDebug() << "Connected to: " << url.toString();
	emit connected();
}


void GosumemoryClient::onMessageReceived(QString message)
{
	//TODO: to prevent flood, add flag to prevent the emission of the signal
	qDebug() << "GosumemoryClient: message received";
	// qDebug() << "Message received from: " << url.toString() << message;
	emit messageReceived(message);
}


void GosumemoryClient::onDisconnected()
{
	qDebug() << "Disconnected from: " << url.toString();
	emit disconnected();
}

void GosumemoryClient::setUrl(const QUrl &url)
{
	this->url = url;
	restart();
}
