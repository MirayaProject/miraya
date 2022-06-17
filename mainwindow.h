#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>

#include "setupwizard.h"
#include "gosumemoryClient.h"

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

	void on_gosumemoryClient_messageReceived(QString message);

private:
	Ui::MainWindow *ui;
	SetupWizard *setupWizard;
	GosumemoryClient *gosumemoryClient;
};

#endif // MAINWINDOW_H
