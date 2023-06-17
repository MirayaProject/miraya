#include "utils.h"

Utils::Utils()
{
}

/**
 * https://regexr.com/6pct6 regex for osu beatmap urls
 */
QStringList Utils::getOsuBeatmapUrls(QString message)
{
	QRegularExpression rx("(https?:\\/\\/)?(osu|old).ppy.sh\\/(p|b|beatmaps|beatmapsets|s)\\/(beatmap\\?b=)?([\\d]+#(osu|taiko|mania|fruits)\\/[\\d]+|[\\d]+)(\\&m=[\\d]*)?");
	QStringList list;
	QRegularExpressionMatchIterator i = rx.globalMatch(message);
	while (i.hasNext()) {
		QRegularExpressionMatch match = i.next();
		list.append(match.captured(0));
	}
	return list;
}


QStringList Utils::getUrls(QString message)
{
	QStringList list;
	QRegularExpression urlRegex("\\b(\\S+\\.\\S+)");
	QRegularExpressionMatchIterator matchIterator = urlRegex.globalMatch(message);
	while(matchIterator.hasNext()) {
		QRegularExpressionMatch match = matchIterator.next();
		QString url = match.captured(0);
		list.append(url);
	}
	return list;
}
