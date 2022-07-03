#ifndef TWITCHCOMMANDHANDLER_H
#define TWITCHCOMMANDHANDLER_H

#include <QString>

#include "twitchdatawrapper.h"
#include "gosumemorydatawrapper.h"

class TwitchCommandHandler
{

public:
	TwitchCommandHandler();
	TwitchCommandHandler(TwitchDataWrapper *twitchData, GosuMemoryDataWrapper *gosumemoryData);
	void setGosumemoryData(GosuMemoryDataWrapper *gosumemoryData);
	void setTwitchDataWrapper(TwitchDataWrapper *twitchData);
	QString getResponse();

private:
	TwitchDataWrapper *twitchData;
	GosuMemoryDataWrapper *gosumemoryData;
};

#endif // TWITCHCOMMANDHANDLER_H
