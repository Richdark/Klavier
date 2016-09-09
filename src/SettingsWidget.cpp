#include "include/SettingsWidget.h"
#include <QMessageBox>

SettingsWidget::SettingsWidget()
{
	this->ui.setupUi(this);

	// plain widget with a title and a close button
	this->setWindowFlags(Qt::Widget | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

	// connect GUI events to update method
	this->connect(this->ui.inputIns, SIGNAL(clicked(bool)), this, SLOT(updateSettingsStruct()));
	this->connect(this->ui.inputK, SIGNAL(clicked(bool)), this, SLOT(updateSettingsStruct()));
}

void SettingsWidget::initSettings(KlavierUtils::Settings * settings)
{
	this->appSettings = settings;

	this->updateSettingsGui();
}

void SettingsWidget::updateSettingsStruct()
{
	// change accent key
	if (this->ui.inputIns->isChecked())
	{
		this->appSettings->input = KlavierUtils::AccentInput::InsKey;
	}
	else
	{
		this->appSettings->input = KlavierUtils::AccentInput::KKey;
	}

	emit this->settingsChanged();
}

void SettingsWidget::updateSettingsGui()
{
	// change accent key
	if (this->appSettings->input == KlavierUtils::AccentInput::InsKey)
	{
		this->ui.inputIns->setChecked(true);
		this->ui.inputK->setChecked(false);
	}
	else
	{
		this->ui.inputIns->setChecked(false);
		this->ui.inputK->setChecked(true);
	}
}

SettingsWidget::~SettingsWidget()
{
}
