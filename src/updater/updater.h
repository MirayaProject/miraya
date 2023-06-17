#ifndef UPDATER_H
#define UPDATER_H

#include <QCoreApplication>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QVersionNumber>

class Updater : public QObject
{
	Q_OBJECT
public:
	explicit Updater(QObject *parent = nullptr);
	void checkVersion();

signals:
	void newVersionAvailable();

private slots:
	void onReplyFinished(QNetworkReply *reply);
};

#endif // UPDATER_H
