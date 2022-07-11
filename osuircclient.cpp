#include "osuircclient.h"

OsuIrcClient::OsuIrcClient(
	const QString &nickname,
	const QString &password,
	const QString &server,
	const int &port,
	QObject *parent
) : QObject(parent), nickname(nickname), password(password), server(server), port(port)
{
	connect(&socket, &QTcpSocket::connected, this, &OsuIrcClient::onConnected);
	connect(&socket, &QTcpSocket::disconnected, this, &OsuIrcClient::onDisconnected);
}


void OsuIrcClient::init(){
	socket.connectToHost(server, port);
	socket.write("PASS " + password.toLocal8Bit() + " \r\n");
	socket.write("USER " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " :" + nickname.toLocal8Bit() + " \r\n");
	socket.write("NICK " + nickname.toLocal8Bit() + " \r\n");
	sendMsg("Ready to process requests");
}


void OsuIrcClient::restart()
{
	socket.close();
	init();
}


void OsuIrcClient::onConnected()
{
	qDebug() << "Connected to: " << socket.peerAddress().toString();
	emit connected();
}


void OsuIrcClient::onDisconnected()
{
	qDebug() << "Disconnected from: " << socket.peerAddress().toString();
	emit disconnected();
}


void OsuIrcClient::setNick(const QString &nickname)
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


void OsuIrcClient::sendMsg(QString message)
{
	socket.write("PRIVMSG " + nickname.toLocal8Bit() + " " + message.toLocal8Bit() + " \r\n");
}


void OsuIrcClient::sendMap(QUrl url, TwitchDataWrapper message)
{
	// TODO: the map embed should have the map name.
	// Scraping is needed.

	qDebug() << "Sending map: " << url.toString() << " by " << message.getUsername();

	socket.write(
		"PRIVMSG "
		+ nickname.toLocal8Bit()
		+ " [" + url.toString().toLocal8Bit() + " Map request] "
		+ "sent by " + message.getUsername().toLocal8Bit()
		+ " \r\n"
	);
}
