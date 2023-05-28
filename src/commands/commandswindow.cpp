#include "commandswindow.h"
#include "ui_commandswindow.h"

CommandsWindow::CommandsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommandsWindow)
{
    ui->setupUi(this);
}

CommandsWindow::~CommandsWindow()
{
    delete ui;
}
