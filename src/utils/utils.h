#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

class Utils
{
public:
	Utils();
	static QStringList getOsuBeatmapUrls(QString message);
	static QStringList getUrls(QString message);
};

#endif // UTILS_H
