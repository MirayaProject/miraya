#include "twitchcommandhandler.h"

TwitchCommandHandler::TwitchCommandHandler()
{
	twitchData = nullptr;
	gosumemoryData = nullptr;
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
	return gosumemoryData;
}


TwitchDataWrapper* TwitchCommandHandler::getTwitchData()
{
	return twitchData;
}


void TwitchCommandHandler::setTwitchData(TwitchDataWrapper *twitchData)
{
	this->twitchData = twitchData;
}


/**
 * Returns a response string based on the message received from Twitch chat.
 *
 * @return A string containing the response to the Twitch chat message.
 *
 * @throws None
 */
QString TwitchCommandHandler::getResponse()
{
	QString command = twitchData->getMessage();
	QSettings settings;

	// handling !commands
	if (command.startsWith("!commands")) {
		return getResponseAllCommands();
	}

	// gosumemory dependent commands
	if (command.startsWith("!np") && gosumemoryData != nullptr) {
		return getResponseNowPlaying();
	}
	else if (command.startsWith("!skin") && gosumemoryData != nullptr) {
		return getResponseSkin();
	}

	// static user commands
	QString response = getResponseStaticCommands();
	if (!response.isEmpty()){
		return response;
	}
	return QString();
}

/**
 * Returns a QString response for static commands saved in QSettings.
 *
 * @return QString response for the given static command, or an empty QString
 * if the command is not found.
 *
 * @throws None
 */
QString TwitchCommandHandler::getResponseStaticCommands()
{
	QSettings settings;
	QString command = twitchData->getMessage();

	settings.beginGroup("command");
	QStringList commands = settings.childKeys();
	auto it = std::find_if(commands.begin(), commands.end(), [&](const QString& savedCommand){
		return command.startsWith(savedCommand);
	});
	if (it != commands.end()) {
		QString response = settings.value(*it).toString();
		return response;
	}
	settings.endGroup();
	return QString();
}

/**
 * Returns a QString containing a list of all available Twitch commands.
 *
 * @return A QString containing the available Twitch commands.
 *
 * @throws None
 */
QString TwitchCommandHandler::getResponseAllCommands()
{
	QSettings settings;
	QString command = twitchData->getMessage();
	if (!command.startsWith("!commands")) {
		return QString();
	}

	settings.beginGroup("command");
	QStringList commands;
	commands << "!np" << "!skin" << settings.childKeys();
	settings.endGroup();
	return QString("Available commands: %1").arg(commands.join(' '));
}

/**
 * Returns a QString of the currently playing song's artist, title, difficulty, mapper, and map url formatted as:
 * "Now playing: artist - title [difficulty] by mapper - map url".
 *
 * @return QString of the currently playing song's information
 */
QString TwitchCommandHandler::getResponseNowPlaying()
{
	QString mapName = gosumemoryData->getMapName();
	QString mapArtist = gosumemoryData->getMapArtist();
	QString mapDiff = gosumemoryData->getMapDifficulty();
	QString mapMapper = gosumemoryData->getMapMapper();
	QString mapUrl = gosumemoryData->getMapUrl();
	return QString("Now playing: %1 - %2 [%3] by %4 - %5").arg(mapArtist, mapName, mapDiff, mapMapper, mapUrl);
}

/**
 * Returns a QString representing the response for the current skin.
 *
 * @return QString containing the current skin name and, if available, a download URL for the skin.
 *
 * @throws None
 */
QString TwitchCommandHandler::getResponseSkin()
{
	QSettings settings;
	QString skinName = gosumemoryData->getSkinName();
	QString skinResponse = QString("skin/%1").arg(skinName);

	if (settings.contains(skinResponse)) {
		QString skinDownloadUrl = settings.value(skinResponse).toString();
		return QString("Current skin: %1 || Download: %2").arg(skinName, skinDownloadUrl);
	}
	return QString("Current skin: %1").arg(skinName);
}
