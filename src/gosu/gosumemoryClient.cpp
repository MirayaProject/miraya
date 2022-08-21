#include "gosumemoryClient.h"

GosumemoryClient::GosumemoryClient(
	const QUrl &url,
	QObject *parent
) : QObject(parent), url(url)
{
	initSignals();
	enableRead(true);
}

GosumemoryClient::GosumemoryClient(QObject *parent) : QObject(parent)
{
	initSignals();
	enableRead(true);
}


void GosumemoryClient::initSignals()
{
	connect(&socket, &QWebSocket::connected, this, &GosumemoryClient::onConnected);
	connect(&socket, &QWebSocket::textMessageReceived, this, &GosumemoryClient::onTextMessageReceived);
	connect(&socket, &QWebSocket::disconnected, this, &GosumemoryClient::onDisconnected);
}


void GosumemoryClient::init()
{
	refreshData();
	qDebug() << "Connecting to: " << url.toString();
	socket.open(QUrl(url));
}


void GosumemoryClient::refreshData()
{
	qDebug() << "[Gosumemory] Refreshing data...";
	QSettings settings;

	setUrl(
		"ws://"
		+ settings.value("gosumemory/ip").toString()
		+ ":"
		+ settings.value("gosumemory/port").toString()
		+ "/ws"
	);
}


void GosumemoryClient::restart()
{
	socket.close();
	init();
}


void GosumemoryClient::onConnected()
{
	qDebug() << "[Gosumemory] Connected to: " << url.toString();
	emit connected();
}


void GosumemoryClient::onTextMessageReceived(QString message)
{
	if (readEnabled) {
		// qDebug() << "GosumemoryClient: message received from: " << url.toString() << message;
		emit messageReceived(GosuMemoryDataWrapper(message));
	}
}


void GosumemoryClient::onDisconnected()
{
	qDebug() << "[Gosumemory] Disconnected from: " << url.toString();
	emit disconnected();
}


void GosumemoryClient::setUrl(const QUrl &url)
{
	this->url = url;
}

void GosumemoryClient::enableRead(bool enable)
{
	readEnabled = enable;
}
