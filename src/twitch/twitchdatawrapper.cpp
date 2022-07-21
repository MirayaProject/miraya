#include "twitchdatawrapper.h"

TwitchDataWrapper::TwitchDataWrapper(QString &data)
	: data(data)
{
	parseData();
}


void TwitchDataWrapper::parseData()
{
	message = data.mid(data.indexOf(":", 1) + 1).trimmed();
	username = data.mid(data.indexOf("!", 1) + 1, data.indexOf("!", 1) - 1);
}


QString TwitchDataWrapper::getMessage()
{
	return message;
}


QString TwitchDataWrapper::getUsername()
{
	return username;
}
