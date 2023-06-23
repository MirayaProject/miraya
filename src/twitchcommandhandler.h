#ifndef TWITCHCOMMANDHANDLER_H
#define TWITCHCOMMANDHANDLER_H

#include <QSettings>
#include <QString>

#include "twitchdatawrapper.h"
#include "osu/data/gosu/gosumemorydatawrapper.h"

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
	QString getResponseStaticCommands();
	QString getResponseAllCommands();
	QString getResponseNowPlaying();
	QString getResponseSkin();

	TwitchDataWrapper *twitchData;
	GosuMemoryDataWrapper *gosumemoryData;
};

#endif // TWITCHCOMMANDHANDLER_H
