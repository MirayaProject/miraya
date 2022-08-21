#include "osuircclient.h"

OsuIrcClient::OsuIrcClient(
	const QString &nickname,
	const QString &password,
	const QString &server,
	const int &port,
	QObject *parent
) : QObject(parent), nickname(nickname), password(password), server(server), port(port)
{
	initSignals();
}


OsuIrcClient::OsuIrcClient(QObject *parent) : QObject(parent)
{
	initSignals();
}


void OsuIrcClient::initSignals()
{
	connect(&socket, &QTcpSocket::connected, this, &OsuIrcClient::onConnected);
	connect(&socket, &QTcpSocket::readyRead, this, &OsuIrcClient::onReadyRead);
	connect(&socket, &QTcpSocket::disconnected, this, &OsuIrcClient::onDisconnected);
}


void OsuIrcClient::init()
{
	refreshData();
	qDebug() << "[osu!IRC] Connecting to: " << server << ":" << port;

	socket.connectToHost(server, port);
	socket.write("PASS " + password.toLocal8Bit() + "\r\n");
	socket.write("USER " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " :" + nickname.toLocal8Bit() + "\r\n");
	socket.write("NICK " + nickname.toLocal8Bit() + "\r\n");

	sendPrivmsg("Ready to process requests!");
}


void OsuIrcClient::refreshData()
{
	qDebug() << "[osu!IRC] Refreshing data...";
	QSettings settings;

	setNickname(settings.value("osuirc/nick").toString());
	setPassword(settings.value("osuirc/password").toString());
	setServer(settings.value("osuirc/server").toString());
	setPort(settings.value("osuirc/port").toInt());
}


void OsuIrcClient::restart()
{
	socket.close();
	init();
}


void OsuIrcClient::onConnected()
{
	qDebug() << "[osu!IRC] Connected to: " << socket.peerAddress().toString();
	emit connected();
}


void OsuIrcClient::onDisconnected()
{
	qDebug() << "[osu!IRC] Disconnected from: " << socket.peerAddress().toString();
	emit disconnected();
}


void OsuIrcClient::setNickname(const QString &nickname)
{
	this->nickname = nickname;
}


void OsuIrcClient::setPassword(const QString &password)
{
	this->password = password;
}


void OsuIrcClient::setServer(const QString &server)
{
	this->server = server;
}


void OsuIrcClient::setPort(const int &port)
{
	this->port = port;
}


void OsuIrcClient::sendPrivmsg(QString message)
{
	socket.write("PRIVMSG " + nickname.toLocal8Bit() + " :" + message.toLocal8Bit() + "\r\n");
}


void OsuIrcClient::sendMap(QUrl url, TwitchDataWrapper message)
{
	// TODO: the map embed should have the map name.
	// Scraping is needed.

	qDebug() << "[osu!IRC] Sending map-request: " << url.toString() << " by " << message.getUsername();

	QString msg = " [" + url.toString() + " Map request] " + "sent by " + message.getUsername() + "\r\n";
	sendPrivmsg(msg);
}

void OsuIrcClient::handlePing(QString response)
{
	socket.write("PONG :\r\n");
	qDebug() << "[osu!IRC] PING request handled";
}

void OsuIrcClient::onReadyRead()
{
	auto data = QString(socket.readAll());

	if(data.contains("PING")) {
		handlePing(data.split(" ").last().toLocal8Bit());
	}
	emit readyRead();
}