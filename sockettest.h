#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class SocketTest : public QObject {
	Q_OBJECT

	public:
		explicit SocketTest(QObject *parent = nullptr);

		void connect();
		void disconnect();

	private:
		QTcpSocket *socket;

	signals:

	public slots:

};

#endif