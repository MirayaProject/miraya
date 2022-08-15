#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
#include <QListWidgetItem>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

#include "setupwizard.h"
#include "twitchClient.h"
#include "twitchdatawrapper.h"
#include "twitchcommandhandler.h"
#include "gosumemoryClient.h"
#include "gosumemorydatawrapper.h"
#include "osuircclient.h"
#include "preferences.h"
#include "utils.h"

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
		void on_init();
		void on_actionStart_Setup_triggered();
		void on_actionGithub_triggered();
		void on_actionDiscord_triggered();
		void on_actionAbout_triggered();
		void on_actionPreferences_triggered();

		void on_setupFinished(QJsonObject json);

		void on_twitchClient_connected();
		void on_gosumemoryClient_connected();
		void on_osuIrcClient_connected();
		void on_twitchClient_disconnected();
		void on_gosumemoryClient_disconnected();
		void on_osuIrcClient_disconnected();
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

		QLabel *ircConnectionLabel;
		QLabel *twitchConnectionLabel;
		QLabel *gosumemoryConnectionLabel;
};

#endif // MAINWINDOW_H
