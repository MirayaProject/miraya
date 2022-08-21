#ifndef OSUIRCCLIENT_H
#define OSUIRCCLIENT_H

#include <QObject>
#include <QSettings>
#include <QTcpSocket>
#include <QUrl>

#include "twitchdatawrapper.h"

class OsuIrcClient : public QObject {
	Q_OBJECT

	public:
		explicit OsuIrcClient(
			const QString &nickname,
			const QString &password,
			const QString &server,
			const int &port,
			QObject *parent = nullptr
		);
		void init();
		void restart();
		void handlePing(QString response);
		void setNickname(const QString &nickname);
		void setPassword(const QString &password);
		void setServer(const QString &server);
		void setPort(const int &port);
		void sendPrivmsg(QString message);
		void sendMap(QUrl url, TwitchDataWrapper message);

	private:
		void refreshData();
		QString nickname;
		QString password;
		QString server;
		int port;
		QTcpSocket socket;

	signals:
		void connected();
		void readyRead();
		void disconnected();

	public slots:
		void onConnected();
		void onReadyRead();
		void onDisconnected();
};

#endif // OSUIRCCLIENT_H
