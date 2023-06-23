#ifndef GOSUMEMORYDATAWRAPPER_H
#define GOSUMEMORYDATAWRAPPER_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class GosuMemoryDataWrapper
{
	public:
		GosuMemoryDataWrapper();
		GosuMemoryDataWrapper(QString &data);
		QString getMapName();
		QString getMapArtist();
		QString getMapMapper();
		QString getMapDifficulty();
		QString getMapUrl();
		QString getSkinName();

	private:
		QString data;
		QJsonObject json;

		void parseData();
		QJsonObject getBeatmapMetadata();
};

#endif // GOSUMEMORYDATAWRAPPER_H
