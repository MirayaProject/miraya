#include <QDesktopServices>
#include <QUrl>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setupWizard = new SetupWizard(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionStart_Setup_triggered()
{
  connect(setupWizard, &SetupWizard::wizardFinished, this, &MainWindow::on_setupFinished);
  setupWizard->show();
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
