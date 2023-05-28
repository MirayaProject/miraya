#ifndef COMMANDSWINDOW_H
#define COMMANDSWINDOW_H

#include <QDialog>

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
    Ui::CommandsWindow *ui;
};

#endif // COMMANDSWINDOW_H
