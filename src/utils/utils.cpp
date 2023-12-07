#include "utils.h"


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

int Utils::getBeatmapIdFromOsuBeatmapLink(QString link)
{
	qDebug() << "getBeatmapIdFromOsuBeatmapLink: " << link;

	// https://osu.ppy.sh/beatmapsets/2055856#taiko/4295990
	QRegularExpression rx("(b=|b/|beatmapsets/\\d+#osu/|beatmapsets/\\d+#taiko/|beatmapsets/\\d+#fruits/|beatmapsets/\\d+#mania/)(\\d+)");
	QRegularExpressionMatch match = rx.match(link);
	if (match.hasMatch()) {
		int id = match.captured(2).toInt();
		qDebug() << "found beatmap id: " << id;
		return id;
	}
	return -1;
}
