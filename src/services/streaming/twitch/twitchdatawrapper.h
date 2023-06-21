#ifndef TWITCHDATAWRAPPER_H
#define TWITCHDATAWRAPPER_H

#include <QString>
#include "streamingServiceDataWrapper.h"

class TwitchDataWrapper : public StreamingServiceDataWrapper
{
public:
	TwitchDataWrapper(QString &data);
	QString getMessage();
	QString getUsername();

private:
	void parseData();
	QString data;
	QString message;
	QString username;
};

#endif // TWITCHDATAWRAPPER_H
