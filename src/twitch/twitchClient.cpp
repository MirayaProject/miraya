#include "twitchClient.h"

TwitchClient::TwitchClient(
	const QUrl &url,
	const QString &botNick,
	const QString &oauth,
	const QString &channel,
	QObject *parent
) : QObject(parent), url(url), oauth(oauth), botNick(botNick), channel(channel)
{
	connect(&socket, &QWebSocket::connected, this, &TwitchClient::onConnected);
	connect(&socket, &QWebSocket::textMessageReceived, this, &TwitchClient::onTextMessageReceived);
	connect(&socket, &QWebSocket::disconnected, this, &TwitchClient::onDisconnected);
}


void TwitchClient::init()
{
	qDebug() << "Connecting to: " << url.toString();
	socket.open(QUrl(url));
}


void TwitchClient::restart()
{
	socket.close();
	init();
}


void TwitchClient::sendChatMessage(QString message)
{
	qDebug() << "Sending channel message: " << message;
	socket.sendTextMessage("PRIVMSG #" + channel + " :" + message);
}


void TwitchClient::sendMessage(QString message)
{
	qDebug() << "Sending message: " << message;
	socket.sendTextMessage(message);
}


void TwitchClient::onConnected()
{
	qDebug() << "Connected to: " << url.toString();
	emit connected();
	sendMessage("PASS " + oauth);
	sendMessage("NICK " + botNick);
	sendMessage("JOIN #" + channel);
}


void TwitchClient::onTextMessageReceived(QString message)
{
	auto wrappedMessage = TwitchDataWrapper(message);
	qDebug() << "Message received from: " << url.toString();

	if (shouldBeFiltered(message)) {
		qDebug() << "Message filtered";
		return;
	}

	if (isCommand(wrappedMessage.getMessage())) {
		qDebug() << "Command received";
		emit commandReceived(wrappedMessage);
	}

	emit textMessageReceived(wrappedMessage);
}


void TwitchClient::handlePing()
{
	sendMessage("PONG :tmi.twitch.tv");
}


bool TwitchClient::shouldBeFiltered(QString message)
{
	// TODO: this can be done better, i think.
	if (message.startsWith("PING")) {
		handlePing();
		return true;
	}

	if (message.startsWith(":tmi.twitch.tv")) {
		return true;
	}

	if (message.startsWith(":" + botNick)) {
		return true;
	}
	return false;
}


bool TwitchClient::isCommand(QString message)
{
	if (message.startsWith("!")) {
		return true;
	}
	return false;
}


void TwitchClient::onDisconnected()
{
	qDebug() << "Disconnected from:" << url.toString();
	emit disconnected();
}


void TwitchClient::setChannel(QString channel)
{
	this->channel = channel;
}


void TwitchClient::setBotNick(QString botNick)
{
	this->botNick = botNick;
}


void TwitchClient::setOauth(QString oauth)
{
	this->oauth = oauth;
}
