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
	connect(&socket, &QTcpSocket::readyRead, this, &OsuIrcClient::onReadyRead);
	connect(&socket, &QTcpSocket::disconnected, this, &OsuIrcClient::onDisconnected);
}


void OsuIrcClient::init(){
	socket.connectToHost(server, port);
	socket.write("PASS " + password.toLocal8Bit() + "\r\n");
	socket.write("USER " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " :" + nickname.toLocal8Bit() + "\r\n");
	socket.write("NICK " + nickname.toLocal8Bit() + "\r\n");
	sendPrivmsg("Ready to process requests!");
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
	socket.write("PONG :" + response.toLocal8Bit() + "\r\n");
	qDebug() << "[osu!IRC] PING request handled";
}

void OsuIrcClient::onReadyRead()
{
	auto data = QString(socket.readAll()).split("\n");

	foreach (QString str, data){
		if(str.contains("PING")){
			auto ping_msg = str.split(" ");
			handlePing(ping_msg[1]);
		}
	}
	emit readyRead();
}