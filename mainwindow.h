#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
#include <QListWidgetItem>

#include "setupwizard.h"
#include "twitchClient.h"
#include "twitchdatawrapper.h"
#include "twitchcommandhandler.h"
#include "gosumemoryClient.h"
#include "gosumemorydatawrapper.h"
#include "osuircclient.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();


	private slots:
		void on_actionStart_Setup_triggered();
		void on_actionGithub_triggered();
		void on_actionDiscord_triggered();
		void on_actionAbout_triggered();

		void on_setupFinished(QJsonObject json);

		void on_gosumemoryClient_messageReceived(GosuMemoryDataWrapper message);
		void on_twitchClient_messageReceived(TwitchDataWrapper message);
		void on_twitchClient_commandReceived(TwitchDataWrapper command);

	private:
		QListWidgetItem *getTwitchChatMessage(QString username, QString message);
		Ui::MainWindow *ui;
		SetupWizard *setupWizard;
		TwitchClient *twitchClient;
		TwitchCommandHandler *twitchCommandHandler;
		GosumemoryClient *gosumemoryClient;
		OsuIrcClient *osuIrcClient;
};

#endif // MAINWINDOW_H
