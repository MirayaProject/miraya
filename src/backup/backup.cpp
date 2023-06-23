#include "backup.h"


void Backup::backup(QString filePath, bool includeSensitiveInfo)
{
	if (filePath.isEmpty()) {
		return;
	}

	// adding .json if needed
	if(!filePath.endsWith(".json")) {
		filePath.append(".json");
	}

	QFile file(filePath);
	if (!(file.open(QIODevice::WriteOnly | QIODevice::Text))) {
		qDebug() << "[Backup] Cannot open file in write mode";
		file.close();
		return;
	}

	qDebug() << "[Backup] Starting backup...";
	// adding all the keys in a json object and converting it into a string
	QJsonObject jsonObject;
	QSettings settings;
	QStringList keys = settings.allKeys();

	// sensitive info must be excluded
	if(!includeSensitiveInfo) {
		keys.removeIf([](const QString& key){
			return key.startsWith("osuirc") || key.startsWith("twitch");
		});
	}

	for(const QString& key: keys){
		QString value = settings.value(key).toString();
		jsonObject.insert(key, QJsonValue(value));
	}
	QString jsonString = QJsonDocument(jsonObject).toJson();

	// saving the backup
	QTextStream stream(&file);
	stream << jsonString;
	file.close();
	qDebug() << "[Backup] Backup completed";
}

void Backup::restore(QString filePath)
{
	if (filePath.isEmpty()) {
		return;
	}

	QFile file(filePath);
	if (!(file.open(QIODevice::ReadOnly | QIODevice::Text))) {
		qDebug() << "[Backup] Cannot open file in read mode";
		file.close();
		return;
	}

	qDebug() << "[Backup] Starting backup restore...";
	QTextStream stream(&file);
	QString jsonString = stream.readAll();
	file.close();

	QSettings settings;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
	if (!jsonDoc.isNull()){
		QJsonObject jsonObject = jsonDoc.object();
		for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
			QString key = it.key();
			QJsonValue value = it.value();

			settings.setValue(key, value.toString());
		}
	}
	qDebug() << "[Backup] Backup restored successfully";
}
