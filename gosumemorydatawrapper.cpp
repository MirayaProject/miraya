#include "gosumemorydatawrapper.h"

GosuMemoryDataWrapper::GosuMemoryDataWrapper(QString &data)
	: data(data)
{
	parseData();
}

void GosuMemoryDataWrapper::parseData()
{
	json = QJsonDocument::fromJson(data.toUtf8()).object();
}

QJsonObject GosuMemoryDataWrapper::getBeatmapMetadata()
{
	return json["menu"].toObject()["bm"].toObject()["metadata"].toObject();
}

QString GosuMemoryDataWrapper::getMapName()
{
	return getBeatmapMetadata()["title"].toString();
}

QString GosuMemoryDataWrapper::getMapArtist()
{
	return getBeatmapMetadata()["artist"].toString();
}

QString GosuMemoryDataWrapper::getMapMapper()
{
	return getBeatmapMetadata()["mapper"].toString();
}

QString GosuMemoryDataWrapper::getMapDifficulty()
{
	return getBeatmapMetadata()["difficulty"].toString();
}
