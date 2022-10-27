#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QJsonObject>
#include <QJsonDocument>
#include <QLabel>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>
#include <QUrl>

#include "gosumemoryClient.h"
#include "gosumemorydatawrapper.h"
#include "osuircclient.h"
#include "preferences.h"
#include "setupwizard.h"
#include "twitchClient.h"
#include "twitchdatawrapper.h"
#include "twitchcommandhandler.h"
#include "utils.h"
#include "skinsurl.h"


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
		void on_actionSkins_triggered();

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
		void setupSignals();
		void setupStatusbar();
		void setupUi();
		void loadTheme();
		void loadDarkMode();
		QListWidgetItem *getTwitchChatMessage(QString username, QString message);
		Ui::MainWindow *ui;
		TwitchClient *twitchClient;
		TwitchCommandHandler *twitchCommandHandler;
		GosumemoryClient *gosumemoryClient;
		OsuIrcClient *osuIrcClient;

		QLabel *ircConnectionLabel;
		QLabel *twitchConnectionLabel;
		QLabel *gosumemoryConnectionLabel;
};

#endif // MAINWINDOW_H
