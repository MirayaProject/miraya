#include "twitchcommandhandler.h"

TwitchCommandHandler::TwitchCommandHandler()
{

}


TwitchCommandHandler::TwitchCommandHandler(TwitchDataWrapper *twitchData, GosuMemoryDataWrapper *gosumemoryData)
{
	this->twitchData = twitchData;
	this->gosumemoryData = gosumemoryData;
}


void TwitchCommandHandler::setGosumemoryData(GosuMemoryDataWrapper *gosumemoryData)
{
	this->gosumemoryData = gosumemoryData;
}


void TwitchCommandHandler::setTwitchDataWrapper(TwitchDataWrapper *twitchData)
{
	this->twitchData = twitchData;
}


QString TwitchCommandHandler::getResponse()
{
	QString command = twitchData->getMessage();
	if (command.startsWith("!np"))
	{
		auto song = gosumemoryData->getMapName();
		auto artist = gosumemoryData->getMapArtist();
		auto diff = gosumemoryData->getMapDifficulty();
		auto mapper = gosumemoryData->getMapMapper();
		auto url = gosumemoryData->getMapUrl();
		return "Now playing: " + artist + " - " + song + " [" + diff + "] by " + mapper + " - " + url;
	}
	return QString("");
}
