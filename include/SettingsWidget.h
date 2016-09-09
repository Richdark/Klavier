#pragma once

#include <QWidget>
#include "ui_settingswidget.h"
#include "KlavierUtils.h"

class SettingsWidget : public QWidget
{
	Q_OBJECT

public:
	SettingsWidget();
	~SettingsWidget();

	void initSettings(KlavierUtils::Settings * settings);

public slots:
	void updateSettingsStruct();

signals:
	void settingsChanged();

private:
	Ui::SettingsWidget ui;

	KlavierUtils::Settings * appSettings;

	void updateSettingsGui();
};

