#include "commandswindow.h"
#include "ui_commandswindow.h"

CommandsWindow::CommandsWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CommandsWindow)
{
	ui->setupUi(this);
	loadData();
	connect(ui->addCommandBtn, &QPushButton::clicked, this, &CommandsWindow::on_addCommandBtn_clicked);
	connect(ui->removeCommandBtn, &QPushButton::clicked, this, &CommandsWindow::on_removeCommandBtn_clicked);
	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CommandsWindow::on_saveBtn_clicked);
}

CommandsWindow::~CommandsWindow()
{
    delete ui;
}

void CommandsWindow::loadData()
{
	qDebug() << "[Commands] Loading data";
	QSettings settings;
	settings.beginGroup("command");
	QStringList commands = settings.childKeys();

	for (QString command: commands) {
		addRow(command, settings.value(command).toString());
	}
}

void CommandsWindow::addRow(QString command, QString response)
{
	// adding new line
	ui->commandsTable->insertRow(ui->commandsTable->rowCount());
	QTableWidgetItem *commandNameItem = new QTableWidgetItem(command);
	QTableWidgetItem *commandResponseItem = new QTableWidgetItem(response);

	// Command name column
	ui->commandsTable->setItem(
		ui->commandsTable->rowCount() - 1,
		0,
		commandNameItem
	);

	// Command response column
	ui->commandsTable->setItem(
		ui->commandsTable->rowCount() - 1,
		1,
		commandResponseItem
	);
}

void CommandsWindow::on_addCommandBtn_clicked()
{
	int lastRow = ui->commandsTable->rowCount() - 1;
	auto lastCommand = ui->commandsTable->item(lastRow, 0);
	auto lastResponse = ui->commandsTable->item(lastRow, 1);

	bool isLastCommandEmpty = lastCommand != nullptr && lastCommand->text().isEmpty();
	bool isLastResponseEmpty = lastResponse != nullptr && lastResponse->text().isEmpty();

	if (!isLastCommandEmpty && !isLastResponseEmpty){
		addRow("","");
	}
}

void CommandsWindow::on_removeCommandBtn_clicked()
{
	QSettings settings;
	auto selectionModel = ui->commandsTable->selectionModel();
	if (!selectionModel->hasSelection()){
		return;
	}

	auto selected = selectionModel->selectedIndexes();
	for (auto selection : selected) {
		int row = selection.row();
		QString command = ui->commandsTable->item(row, 0)->text();

		settings.remove(QString("command/%1").arg(command));
		ui->commandsTable->removeRow(row);
	}
}

void CommandsWindow::on_saveBtn_clicked()
{
	qDebug() << "[Commands] Saving data...";
	QSettings settings;

	for (int row = 2; row < ui->commandsTable->rowCount(); row++) {
		QTableWidgetItem *commandNameItem = ui->commandsTable->item(row, 0);
		QTableWidgetItem *commandResponseItem  = ui->commandsTable->item(row, 1);

		if (commandResponseItem == nullptr || commandNameItem == nullptr) {
			return;
		}

		QString commandName = commandNameItem->text();
		QString commandResponse  = commandResponseItem->text();

		if (!commandName.startsWith("!")) {
			commandName.prepend("!");
		}

		QString key = QString("command/%1").arg(commandName);
		settings.setValue(key, commandResponse);
		qDebug() << "[Commands] " << commandName << "has been saved";
	}
	qDebug() << "[Commands] Data saved";
	accept();
}