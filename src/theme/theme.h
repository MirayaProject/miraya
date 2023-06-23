#ifndef THEME_H
#define THEME_H

#include <QDebug>
#include <QStyleFactory>
#include <QObject>
#include <QSettings>
#include <QPalette>
#include <QColor>
#include <QApplication>

class Theme : public QObject
{
	Q_OBJECT
public:
	static void loadTheme();
	static void loadDarkMode();
	static void loadLightMode();
	static void loadThemeFromSetting(QVariant darkModeSettings);
	static void loadDefaultThemeWindows();
};

#endif // THEME_H
