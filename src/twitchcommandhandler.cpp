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
	if (gosumemoryData == nullptr) {
		return QString("");
	}
	QSettings settings;

	settings.beginGroup("command");
	QStringList commands = settings.childKeys();
	for (QString savedCommand: commands) {
		if (command.startsWith(savedCommand)){
			QString response = settings.value(savedCommand).toString();
			return response;
		}
	}

	settings.endGroup();


	if (command.startsWith("!np")) {
		auto song = gosumemoryData->getMapName();
		auto artist = gosumemoryData->getMapArtist();
		auto diff = gosumemoryData->getMapDifficulty();
		auto mapper = gosumemoryData->getMapMapper();
		auto url = gosumemoryData->getMapUrl();
		return QString("Now playing: %1 - %2 [%3] by %4 - %5").arg(artist, song, diff, mapper, url);
	}

	else if (command.startsWith("!skin")) {
		QString skin = gosumemoryData->getSkinName();
		QString settingsPath = QString("skin/%1").arg(skin);
		if (settings.contains(settingsPath)) {
			QString skinDownloadUrl = settings.value(settingsPath).toString();
			return QString("Current skin: %1 || Download: %2").arg(skin, skinDownloadUrl);
		}
		return QString("Current skin: %1").arg(skin);
	}
	return QString("");
}
