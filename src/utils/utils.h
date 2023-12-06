#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

class Utils
{
public:
	static QStringList getOsuBeatmapUrls(QString message);
	static QStringList getUrls(QString message);
	static int getBeatmapIdFromOsuBeatmapLink(QString link);
};

#endif // UTILS_H
