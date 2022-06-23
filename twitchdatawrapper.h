#ifndef TWITCHDATAWRAPPER_H
#define TWITCHDATAWRAPPER_H

#include <QObject>
#include <QDebug>

class TwitchDataWrapper : public QObject
{
	Q_OBJECT

	public:
		explicit TwitchDataWrapper(
			const QString &data,
			QObject *parent = nullptr
		);
		QString getMessage();
		QString getUsername();

	private:
		void parseData();
		QString data;
		QString message;
		QString username;

};

#endif // TWITCHDATAWRAPPER_H
