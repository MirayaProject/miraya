#ifndef TWITCHCLIENT_H
#define TWITCHCLIENT_H

#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QUrl>
#include <QWebSocket>

#include "twitchdatawrapper.h"

class TwitchClient : public QObject {
	Q_OBJECT

	public:
		explicit TwitchClient(QObject *parent = nullptr);
		explicit TwitchClient(
			const QUrl &url,
			const QString &botNick,
			const QString &oauth,
			const QString &channel,
			QObject *parent = nullptr
		);
		void init();
		void restart();
		void setChannel(QString channel);
		void setBotNick(QString botNick);
		void setOauth(QString oauth);
		void setUrl(QUrl url);
		void sendChatMessage(QString message);

	private:
		void handlePing();
		bool isCommand(QString message);
		void initSignals();
		void refreshData();
		void sendMessage(QString message);
		bool shouldBeFiltered(QString message);

		QWebSocket socket;
		QUrl url;
		QString oauth;
		QString botNick;
		QString channel;

	signals:
		void connected();
		void textMessageReceived(TwitchDataWrapper message);
		void commandReceived(TwitchDataWrapper command);
		void disconnected();

	public slots:
		void onConnected();
		void onTextMessageReceived(QString message);
		void onDisconnected();
};

#endif
