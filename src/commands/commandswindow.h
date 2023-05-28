#ifndef COMMANDSWINDOW_H
#define COMMANDSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>

namespace Ui {
	class CommandsWindow;
}

class CommandsWindow : public QDialog
{
	Q_OBJECT

public:
	explicit CommandsWindow(QWidget *parent = nullptr);
	~CommandsWindow();

private:
  void on_addCommandBtn_clicked();
  void on_removeCommandBtn_clicked();
	void on_saveBtn_clicked();

	void loadData();
	void addRow(QString command, QString response);

	Ui::CommandsWindow *ui;
};

#endif // COMMANDSWINDOW_H
