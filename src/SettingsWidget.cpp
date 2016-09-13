#include "include/SettingsWidget.h"
#include <QMessageBox>

SettingsWidget::SettingsWidget()
{
	this->ui.setupUi(this);

	// plain widget with a title and a close button
	this->setWindowFlags(Qt::Widget | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

	// connect GUI events to the update method
	this->connect(this->ui.inputIns, SIGNAL(clicked(bool)), this, SLOT(updateSettingsStruct()));
	this->connect(this->ui.inputK, SIGNAL(clicked(bool)), this, SLOT(updateSettingsStruct()));
	this->connect(this->ui.altCheckbox, SIGNAL(clicked(bool)), this, SLOT(updateSettingsStruct()));
	this->connect(this->ui.ctrlCheckbox, SIGNAL(clicked(bool)), this, SLOT(updateSettingsStruct()));
	this->connect(this->ui.shiftCheckbox, SIGNAL(clicked(bool)), this, SLOT(updateSettingsStruct()));
	this->connect(this->ui.secondaryKeyComboBox, SIGNAL(activated(int)), this, SLOT(updateSettingsStruct()));

	// fill up hotkey combo box
	QStringList hotkey_list = {
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
		"M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
		"Y", "Z", "Tab", "Space", "Insert", "Delete", "Home", "End",
		"Page up", "Page down"
	};
	this->ui.secondaryKeyComboBox->addItems(hotkey_list);
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

	// hotkey modifier
	UINT hotkey_modifiers = MOD_NOREPEAT;

	if (this->ui.altCheckbox->isChecked())
	{
		hotkey_modifiers |= MOD_ALT;
	}

	if (this->ui.ctrlCheckbox->isChecked())
	{
		hotkey_modifiers |= MOD_CONTROL;
	}

	if (this->ui.shiftCheckbox->isChecked())
	{
		hotkey_modifiers |= MOD_SHIFT;
	}

	this->appSettings->hotkey_modifiers = hotkey_modifiers;

	// actual hotkey
	UINT hotkey = KlavierUtils::HotkeyCodes.at(this->ui.secondaryKeyComboBox->currentText().toStdString());
	this->appSettings->hotkey = hotkey;
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

	// Alt hotkey modifier
	if ((this->appSettings->hotkey_modifiers & MOD_ALT) == MOD_ALT)
	{
		this->ui.altCheckbox->setChecked(true);
	}
	else
	{
		this->ui.altCheckbox->setChecked(false);
	}

	// Ctrl hotkey modifier
	if ((this->appSettings->hotkey_modifiers & MOD_CONTROL) == MOD_CONTROL)
	{
		this->ui.ctrlCheckbox->setChecked(true);
	}
	else
	{
		this->ui.ctrlCheckbox->setChecked(false);
	}

	// Shift hotkey modifier
	if ((this->appSettings->hotkey_modifiers & MOD_SHIFT) == MOD_SHIFT)
	{
		this->ui.shiftCheckbox->setChecked(true);
	}
	else
	{
		this->ui.shiftCheckbox->setChecked(false);
	}

	// actual hotkey
	this->ui.secondaryKeyComboBox->setCurrentText(QString::fromStdString(KlavierUtils::HotkeyLabels.at(this->appSettings->hotkey)));
}

SettingsWidget::~SettingsWidget()
{
}
