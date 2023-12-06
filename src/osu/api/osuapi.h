#ifndef OSUAPI_H
#define OSUAPI_H

#include <QUrl>
#include <QSettings>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

#include "api/auth/clientCredentialsFlow.h"

class OsuApi : public QObject
{
	public:
		OsuApi();
		QJsonObject getBeatmapInfo(int beatmapId);

	private:
		QString clientId;
		QString clientSecret;
		QString oAuthUrl;
		QJsonObject token;
};

#endif // OSUAPI_H
