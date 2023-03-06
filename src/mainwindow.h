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

#include "htmldelegate.h"
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
		void on_btnStart_clicked();
		void on_actionStart_Setup_triggered();
		void on_actionGithub_triggered();
		void on_actionDiscord_triggered();
		void on_actionAbout_triggered();
		void on_actionPreferences_triggered();
		void on_actionSkins_triggered();

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


	private:
		void setupSignals();
		void setupStatusbar();
		void setupUi();

		void loadTheme();
		void loadDarkMode();
		void loadLightMode();
		void loadThemeFromSetting(QVariant darkModeSettings);
		void loadDefaultThemeWindows();

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
