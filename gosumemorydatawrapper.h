#ifndef GOSUMEMORYDATAWRAPPER_H
#define GOSUMEMORYDATAWRAPPER_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class GosuMemoryDataWrapper
{
	public:
		GosuMemoryDataWrapper(QString &data);
		QString getMapName();
		QString getMapArtist();
		QString getMapMapper();
		QString getMapDifficulty();

	private:
		QString data;
		QJsonObject json;

		void parseData();
		QJsonObject getBeatmapMetadata();
};

#endif // GOSUMEMORYDATAWRAPPER_H
