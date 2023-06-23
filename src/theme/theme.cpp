#include "theme.h"


void Theme::loadTheme()
{
	qDebug() << "[Theme] Loading theme...";
	QSettings settings;
	bool isDarkMode;
	auto darkModeSetting = settings.value("theme/darkMode");
	auto darkModeSettingExists = !darkModeSetting.isNull();

	if (darkModeSettingExists) {
		// If present, prefer local settings.
		loadThemeFromSetting(darkModeSetting);
	}
	else {
		#ifdef Q_OS_WIN
			loadDefaultThemeWindows();
		#else
			loadLightMode();
		#endif
	}
	qDebug() << "[Theme] Theme loaded";
}


void Theme::loadThemeFromSetting(QVariant darkModeSetting)
{
	qDebug() << "[Theme] Loading theme from settings...";
	bool isDarkMode = darkModeSetting.toBool();
	if (isDarkMode) {
		loadDarkMode();
	}
	else {
		loadLightMode();
	}
	qDebug() << "[Theme] Theme loaded from settings";
}


void Theme::loadDefaultThemeWindows()
{
	qDebug() << "[Theme](Windows) Loading system theme...";

	// In windows>=10, you can set a default behaviour for app themes in the settings menu.
	// TODO: Check for major and minor version of windows.
	// Perhaps this can be used in linux and macos too?
	QSettings windowsSettings(
		"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
		QSettings::NativeFormat
	);
	auto isDarkMode = windowsSettings.value("AppsUseLightTheme") == 0;

	if (isDarkMode) {
		loadDarkMode();
	}
	qDebug() << "[Theme](Windows) System theme loaded";
}


void Theme::loadDarkMode()
{
	qDebug() << "[Theme] Loading dark theme...";
	qApp->setStyle(QStyleFactory::create("Fusion"));
	QPalette darkPalette;
	QColor darkColor = QColor(45,45,45);
	QColor disabledColor = QColor(127,127,127);

	darkPalette.setColor(QPalette::Window, darkColor);
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(18,18,18));
	darkPalette.setColor(QPalette::AlternateBase, darkColor);
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
	darkPalette.setColor(QPalette::Button, darkColor);
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);
	darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

	qApp->setPalette(darkPalette);
	qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
	qDebug() << "[Theme] Dark theme loaded";
}


void Theme::loadLightMode()
{
	qDebug() << "[Theme] Loading light theme...";
	QPalette lightPalette;
	qApp->setPalette(lightPalette);
	qApp->setStyleSheet("");
	qDebug() << "[Theme] Light theme loaded";
	// TODO: implement? Is it actually needed?
}
