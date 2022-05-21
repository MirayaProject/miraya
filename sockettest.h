#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QWebSocket>
#include <QDebug>
#include <QUrl>

class SocketTest : public QObject {
	Q_OBJECT

	public:
		explicit SocketTest(const QUrl &url, QObject *parent = nullptr);

		void disconnect();


	private:
		QWebSocket socket;

	signals:

	private Q_SLOTS:
		void onConnected();
		void onTextMessageReceived(QString message);
		void onDisconnected();
};

#endif