#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setupUi();

	QSettings settings;
	twitchClient = new TwitchClient(this);
	gosumemoryClient = new GosumemoryClient(this);
	osuIrcClient = new OsuIrcClient(this);

	twitchCommandHandler = new TwitchCommandHandler();
	updater = new Updater(this);
	updater->checkVersion();

	osuApi = new OsuApi();

	setupSignals();
	if(!settings.value("setup/completed").toBool()){
		on_actionStart_Setup_triggered();
	}
}


MainWindow::~MainWindow()
{
	delete twitchClient;
	delete gosumemoryClient;
	delete osuIrcClient;
	delete twitchCommandHandler;
	delete ui;
}


void MainWindow::setupUi()
{
	setupStatusbar();
	Theme::loadTheme();
}


void MainWindow::setupStatusbar()
{
	twitchConnectionLabel = new QLabel(this);
	gosumemoryConnectionLabel = new QLabel(this);
	ircConnectionLabel = new QLabel(this);

	ui->statusbar->addPermanentWidget(twitchConnectionLabel);
	ui->statusbar->addPermanentWidget(gosumemoryConnectionLabel);
	ui->statusbar->addPermanentWidget(ircConnectionLabel);
}


void MainWindow::setupSignals()
{
	connect(twitchClient, &TwitchClient::connected, this, &MainWindow::onTwitchClientConnected);
	connect(twitchClient, &TwitchClient::disconnected, this, &MainWindow::onTwitchClientDisconnected);
	connect(gosumemoryClient, &GosumemoryClient::connected, this, &MainWindow::onGosumemoryClientConnected);
	connect(gosumemoryClient, &GosumemoryClient::disconnected, this, &MainWindow::onGosumemoryClientDisconnected);
	connect(osuIrcClient, &OsuIrcClient::connected, this, &MainWindow::onOsuIrcClientConnected);
	connect(osuIrcClient, &OsuIrcClient::disconnected, this, &MainWindow::onOsuIrcClientDisconnected);

	connect(twitchClient, &TwitchClient::textMessageReceived, this, &MainWindow::onTwitchClientMessageReceived);
	connect(twitchClient, &TwitchClient::commandReceived, this, &MainWindow::onTwitchClientCommandReceived);
	connect(gosumemoryClient, &GosumemoryClient::messageReceived, this, &MainWindow::onGosumemoryClientMessageReceived);
	connect(updater, &Updater::newVersionAvailable, this, &MainWindow::onNewVersionReceived);
}


void MainWindow::on_actionStart_Setup_triggered()
{
	SetupWizard(this).exec();
}


void MainWindow::on_actionGithub_triggered()
{
	QDesktopServices::openUrl(QUrl("https://www.github.com/MirayaProject/miraya"));
}


void MainWindow::on_actionDiscord_triggered()
{
	QDesktopServices::openUrl(QUrl("https://www.discord.gg/anHrS7p5Sf"));
}


void MainWindow::on_actionAbout_triggered()
{
	return About::show();
}


void MainWindow::on_actionPreferences_triggered()
{
	auto preferences = Preferences(this);
	connect(&preferences, &Preferences::themeChanged, this, &MainWindow::onThemeChanged);
	preferences.exec();
}


void MainWindow::on_actionSkins_triggered()
{
	SkinsUrl(gosumemoryClient, this).exec();
}


void MainWindow::on_actionCommands_triggered()
{
	CommandsWindow(this).exec();
}


void MainWindow::on_btnStart_clicked()
{
	qDebug() << "[MainWindow] init";
	twitchClient->restart();
	gosumemoryClient->restart();
	osuIrcClient->restart();
}


void MainWindow::onThemeChanged()
{
	Theme::loadTheme();
}


void MainWindow::onGosumemoryClientMessageReceived(GosuMemoryDataWrapper message)
{
	// TODO: is this the best way to handle it? shouldn't it be &message?
	delete twitchCommandHandler->getGosumemoryData();
	twitchCommandHandler->setGosumemoryData(new GosuMemoryDataWrapper(message));
	QString title = message.getMapName();
	QString artist = message.getMapArtist();
	ui->nowPlayingLabel->setText(QString("%1 - %2").arg(artist, title));
}


void MainWindow::onTwitchClientMessageReceived(TwitchDataWrapper message)
{
	// TODO: this should not be here
	for (QString url : Utils::getOsuBeatmapUrls(message.getMessage())) {
		qDebug() << "[MainWindow] Osu beatmap url: " << url;

		int beatmapId = Utils::getBeatmapIdFromOsuBeatmapLink(url);
		if (beatmapId > 0) {
			// TODO: also this should not be here
			QJsonObject mapData = osuApi->getBeatmapInfo(beatmapId);
			osuIrcClient->sendMap(mapData, message);
		}
		else {
			osuIrcClient->sendMap(QUrl(url), message);
		}
	}

	QLabel* label = getTwitchChatMessage(message.getUsername(), message.getMessage());
	label->adjustSize();
	QListWidgetItem* item = new QListWidgetItem(ui->twitchChat);
	item->setSizeHint(label->size()); // Set the size hint based on the label's size
	ui->twitchChat->addItem(item);
	ui->twitchChat->setItemWidget(item, label);
	ui->twitchChat->scrollToBottom();
}


void MainWindow::onNewVersionReceived()
{
	qDebug() << "[MainWindow] New version available";
	QMessageBox().information(
		this,
		"New Version Available",
		"There is a new version available! Click <a href='https://github.com/MirayaProject/miraya/releases/latest'>here</a> to check it out!",
		QMessageBox::Ok
	);
}


QLabel* MainWindow::getTwitchChatMessage(QString username, QString message)
{
	QString richTextMsg = getRichTextMessage(message);
	QLabel* label = new QLabel();

	QFont font = label->font();
	font.setPointSize(12);
	label->setFont(font);

	label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	label->setTextFormat(Qt::RichText);
	label->setTextInteractionFlags(Qt::TextBrowserInteraction);
	label->setOpenExternalLinks(true);

	label->setWordWrap(true);
	label->setText(QString("<b>%1</b>: %2").arg(username).arg(richTextMsg));
	label->setMaximumHeight(qMax(label->sizeHint().height(), 44)); //noqa
	return label;
}


QString MainWindow::getRichTextMessage(const QString& message)
{
	auto urls = Utils::getUrls(message);
	QString substitutedMessage = message;
	for (auto url : urls){
		substitutedMessage.replace(url, QString("<a href='%1'>%1</a>").arg(url));
	}
	return substitutedMessage;
}


void MainWindow::onTwitchClientCommandReceived(TwitchDataWrapper command)
{
	twitchCommandHandler->setTwitchData(&command);
	QString response = twitchCommandHandler->getResponse();
	twitchClient->sendChatMessage(response);
}


void MainWindow::onOsuIrcClientConnected()
{
	ircConnectionLabel->setText("IRC ✔️");
}


void MainWindow::onTwitchClientConnected()
{
	twitchConnectionLabel->setText("Twitch ✔️");
}


void MainWindow::onGosumemoryClientConnected()
{
	gosumemoryConnectionLabel->setText("Gosumemory ✔️");
}


void MainWindow::onOsuIrcClientDisconnected()
{
	ircConnectionLabel->setText("IRC ❌");
}


void MainWindow::onTwitchClientDisconnected()
{
	twitchConnectionLabel->setText("Twitch ❌");
}


void MainWindow::onGosumemoryClientDisconnected()
{
	gosumemoryConnectionLabel->setText("Gosumemory ❌");
}
