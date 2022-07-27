#include "twitchcommandhandler.h"

TwitchCommandHandler::TwitchCommandHandler()
{
	this->twitchData = nullptr;
	this->gosumemoryData = nullptr;
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

GosuMemoryDataWrapper* TwitchCommandHandler::getGosumemoryData()
{
	return this->gosumemoryData;
}


TwitchDataWrapper* TwitchCommandHandler::getTwitchData()
{
	return this->twitchData;
}


void TwitchCommandHandler::setTwitchData(TwitchDataWrapper *twitchData)
{
	this->twitchData = twitchData;
}


QString TwitchCommandHandler::getResponse()
{
	QString command = twitchData->getMessage();
	if (this->gosumemoryData == nullptr) {
		return QString("");
	}

	if (command.startsWith("!np")) {
		auto song = gosumemoryData->getMapName();
		auto artist = gosumemoryData->getMapArtist();
		auto diff = gosumemoryData->getMapDifficulty();
		auto mapper = gosumemoryData->getMapMapper();
		auto url = gosumemoryData->getMapUrl();
		return QString("Now playing: " + artist + " - " + song + " [" + diff + "] by " + mapper + " - " + url);
	}
	return QString("");
}
