#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
  class Preferences;
}

class Preferences : public QDialog
{
  Q_OBJECT

public:
  explicit Preferences(QWidget *parent = nullptr);
  ~Preferences();

private:
  Ui::Preferences *ui;
  void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // PREFERENCES_H
