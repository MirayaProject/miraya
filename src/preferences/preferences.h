#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QSettings>
#include <QMessageBox>
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
  QSettings settings;
  void loadSettings();
  void loadTwitchSettings();
  void loadGosuMemorySettings();
  void loadOsuIrcSettings();
  void loadThemeSettings();
  void setupUi();
  void saveSettings();
  void on_saveBtnClicked();
  void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

signals:
  void themeChanged();
};

#endif // PREFERENCES_H
