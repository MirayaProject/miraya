#ifndef CLIENTCREDENTIALSFLOW_H
#define CLIENTCREDENTIALSFLOW_H

#include <QUrl>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

class ClientCredentialsFlow
{
	public:
		static QJsonObject getToken(
			QString clientId,
			QString clientSecret,
			QString oAuthUrl = QString("https://osu.ppy.sh/oauth/token")
		);
};

#endif // CLIENTCREDENTIALSFLOW_H
