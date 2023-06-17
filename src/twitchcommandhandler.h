#ifndef TWITCHCOMMANDHANDLER_H
#define TWITCHCOMMANDHANDLER_H

#include <QString>
#include <QSettings>

#include "twitchdatawrapper.h"
#include "gosumemorydatawrapper.h"

class TwitchCommandHandler
{
public:
	TwitchCommandHandler();
	TwitchCommandHandler(TwitchDataWrapper *twitchData, GosuMemoryDataWrapper *gosumemoryData);
	void setGosumemoryData(GosuMemoryDataWrapper *gosumemoryData);
	void setTwitchData(TwitchDataWrapper *twitchData);
	GosuMemoryDataWrapper* getGosumemoryData();
	TwitchDataWrapper* getTwitchData();
	QString getResponse();

private:
	TwitchDataWrapper *twitchData;
	GosuMemoryDataWrapper *gosumemoryData;
};

#endif // TWITCHCOMMANDHANDLER_H
