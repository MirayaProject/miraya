#ifndef GOSUMEMORYCLIENT_H
#define GOSUMEMORYCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QDebug>
#include <QUrl>

#include "gosumemorydatawrapper.h"

class GosumemoryClient : public QObject {
	Q_OBJECT

	public:
		explicit GosumemoryClient(const QUrl &url, QObject *parent = nullptr);
		void init();
		void setUrl(const QUrl &url);
		void enableRead(bool enable);

	private:
		void restart();
		QWebSocket socket;
		QUrl url;
		bool readEnabled;

	signals:
		void connected();
		void messageReceived(GosuMemoryDataWrapper message);
		void disconnected();

	public slots:
		void onConnected();
		void onTextMessageReceived(QString message);
		void onDisconnected();
};

#endif
