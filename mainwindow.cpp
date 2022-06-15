#include <QDesktopServices>
#include <QUrl>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupwizard.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionStart_Setup_triggered()
{
  // TODO: setupwizard should be a private member of mainwindow instead
  SetupWizard *sw = new SetupWizard(this);
  connect(sw, &SetupWizard::wizardFinished, this, &MainWindow::on_setupFinished);
  sw->show();
}


void MainWindow::on_actionGithub_triggered()
{
  QDesktopServices::openUrl(QUrl("https://www.github.com/MirayaProject/miraya"));
}


void MainWindow::on_actionDiscord_triggered()
{
  QDesktopServices::openUrl(QUrl("https://www.discord.gg/anHrS7p5Sf"));
}

void MainWindow::on_setupFinished(QJsonObject data)
{
  qDebug() << "MainWindow: Setup finished with data:" << data;
}
