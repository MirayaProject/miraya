#include "osuircclient.h"

OsuIrcClient::OsuIrcClient(
    const QString &nickname,
    const QString &password,
    const QString &server,
    const int &port,
    QObject *parent
    ) : QObject(parent), nickname(nickname), password(password), server(server), port(port)
{
    // socket = new QTcpSocket(this);
    connect(&socket, &QTcpSocket::connected, this, &OsuIrcClient::onConnected);
    connect(&socket, &QTcpSocket::disconnected, this, &OsuIrcClient::onDisconnected);
}

void OsuIrcClient::init(){
    socket->connectToHost(server, port);
    socket->write("PASS " + password.toLocal8Bit() + " \r\n");
    socket->write("USER " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " " + nickname.toLocal8Bit() + " :" + nickname.toLocal8Bit() + " \r\n");
    socket->write("NICK " + nickname.toLocal8Bit() + " \r\n");
    socket->write("PRIVMSG " + nickname.toLocal8Bit() + " ReadyToProcessRequests \r\n");
}

void OsuIrcClient::onConnected()
{
    qDebug() << "Connected to: " << socket->peerAddress().toString();
    emit connected();
}

void OsuIrcClient::onDisconnected()
{
    qDebug() << "Disconnected from: " << socket->peerAddress().toString();
    emit disconnected();
}
