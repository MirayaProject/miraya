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
  SetupWizard *sw = new SetupWizard(this);
  sw->show();
}


void MainWindow::on_actionGithub_triggered()
{

}


void MainWindow::on_actionDiscord_triggered()
{

}

