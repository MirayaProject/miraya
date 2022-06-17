#ifndef GOSUMEMORYCLIENT_H
#define GOSUMEMORYCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QDebug>
#include <QUrl>

class GosumemoryClient : public QObject {
	Q_OBJECT

	public:
		explicit GosumemoryClient(const QUrl &url, QObject *parent = nullptr);
		void init();
		void setUrl(const QUrl &url);

	private:
		void restart();
		QWebSocket socket;
		QUrl url;

	signals:
		void connected();
		void messageReceived(QString message);
		void disconnected();

	private slots:
		void onConnected();
		void onTextMessageReceived(QString message);
		void onDisconnected();
};

#endif
