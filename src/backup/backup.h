#ifndef BACKUP_H
#define BACKUP_H

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>
#include <QObject>
#include <QSettings>

class Backup : public QObject
{
	Q_OBJECT
public:
	static void backup(QString filePath, bool includeSensitiveInfo);
	static void restore(QString filePath);
};

#endif // BACKUP_H
