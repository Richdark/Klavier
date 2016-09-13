#pragma once

#include <QtWidgets/QMainWindow>
#include <QSystemTrayIcon>
#include "include/json/json.h"
#include "ui_klavier.h"
#include "KeyboardHook.h"
#include "SettingsWidget.h"
#include "AboutWidget.h"

#define KLAVIER_VERSION 0.1.0

class Klavier : public QMainWindow
{
	Q_OBJECT

public:
	Klavier(QWidget * parent = 0);
	~Klavier();
	KlavierUtils::Settings * getSettings();

public slots:
	void updateSettingsFile();
	void quit();

signals:
	void closed();

private:
	Ui::KlavierClass ui;

	static char * settingsFileName;
	QSystemTrayIcon trayIcon;
	QMenu trayMenu;
	SettingsWidget settingsWindow;
	AboutWidget aboutWindow;
	KlavierUtils::Settings settings;

	void loadSettings();
	void applySettings();
	void createSettingsFile();
	KlavierUtils::Settings settingsDecode(const Json::Value & settings);
	Json::Value settingsEncode(const KlavierUtils::Settings & settings);
	bool nativeEvent(const QByteArray & eventType, void * message, long * result);
};
