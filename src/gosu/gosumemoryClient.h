#ifndef GOSUMEMORYCLIENT_H
#define GOSUMEMORYCLIENT_H

#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QUrl>
#include <QWebSocket>

#include "gosumemorydatawrapper.h"

class GosumemoryClient : public QObject {
	Q_OBJECT

	public:
		explicit GosumemoryClient(QObject *parent = nullptr);
		explicit GosumemoryClient(const QUrl &url, QObject *parent = nullptr);
		void enableRead(bool enable);
		void init();
		void restart();
		void setUrl(const QUrl &url);

	private:
		void initSignals();
		void refreshData();
		bool readEnabled;
		QWebSocket socket;
		QUrl url;

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
