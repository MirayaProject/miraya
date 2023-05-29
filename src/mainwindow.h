#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>
#include <QUrl>

#include "commandswindow.h"
#include "gosumemoryClient.h"
#include "gosumemorydatawrapper.h"
#include "osuircclient.h"
#include "preferences.h"
#include "setupwizard.h"
#include "skinsurl.h"
#include "twitchClient.h"
#include "twitchcommandhandler.h"
#include "twitchdatawrapper.h"
#include "updater.h"
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
		void on_btnStart_clicked();
		void on_actionStart_Setup_triggered();
		void on_actionGithub_triggered();
		void on_actionDiscord_triggered();
		void on_actionAbout_triggered();
		void on_actionPreferences_triggered();
		void on_actionSkins_triggered();
		void on_actionCommands_triggered();

		void onThemeChanged();
		void onTwitchClientConnected();
		void onGosumemoryClientConnected();
		void onOsuIrcClientConnected();
		void onTwitchClientDisconnected();
		void onGosumemoryClientDisconnected();
		void onOsuIrcClientDisconnected();
		void onGosumemoryClientMessageReceived(GosuMemoryDataWrapper message);
		void onTwitchClientMessageReceived(TwitchDataWrapper message);
		void onTwitchClientCommandReceived(TwitchDataWrapper command);
		void onNewVersionReceived();


	private:
		void setupSignals();
		void setupStatusbar();
		void setupUi();

		void loadTheme();
		void loadDarkMode();
		void loadLightMode();
		void loadThemeFromSetting(QVariant darkModeSettings);
		void loadDefaultThemeWindows();

		QLabel *getTwitchChatMessage(QString username, QString message);
		QString getRichTextMessage(const QString& message);
		Ui::MainWindow *ui;
		TwitchClient *twitchClient;
		TwitchCommandHandler *twitchCommandHandler;
		GosumemoryClient *gosumemoryClient;
		OsuIrcClient *osuIrcClient;
		Updater *updater;

		QLabel *ircConnectionLabel;
		QLabel *twitchConnectionLabel;
		QLabel *gosumemoryConnectionLabel;
};

#endif // MAINWINDOW_H
