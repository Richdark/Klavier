#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include "include/klavier.h"

namespace KU = KlavierUtils;
using std::string;

char * Klavier::settingsFileName = "settings.json";

Klavier::Klavier(QWidget *parent) : QMainWindow(parent)
{
	this->ui.setupUi(this);

	this->trayMenu.addAction("Settings", &this->settingsWindow, SLOT(show()));
	this->trayMenu.addAction("About", &this->aboutWindow, SLOT(show()));
	this->trayMenu.addAction("Exit", this, SLOT(quit()));

	// set tray context menu
	this->trayIcon.setContextMenu(&this->trayMenu);
	
	// set tray icon
	this->trayIcon.setIcon(QIcon(":/images/icon.png"));
	this->trayIcon.show();

	// load app settings
	this->loadSettings();
	this->applySettings();
	this->settingsWindow.initSettings(this->getSettings());
	this->connect(&this->settingsWindow, SIGNAL(settingsChanged()), this, SLOT(updateSettingsFile()));
}

KlavierUtils::Settings * Klavier::getSettings()
{
	return &this->settings;
}

void Klavier::quit()
{
	emit this->closed();
}

Klavier::~Klavier()
{
}

void Klavier::loadSettings()
{
	QFileInfo settings_file_info(this->settingsFileName);

	// create settings file if it doesn't exist
	if (!(settings_file_info.exists()))
	{
		this->createSettingsFile();
	}

	QFile settings_file(this->settingsFileName);

	// open settings file for reading
	if (settings_file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream settings_stream(&settings_file);
		Json::Value settings_json;
		Json::Reader json_reader;

		json_reader.parse(settings_stream.readAll().toStdString(), settings_json);

		// decode from Json::Value object to Settings struct
		this->settings = this->settingsDecode(settings_json);

		settings_file.close();
	}
}

void Klavier::applySettings()
{
	KeyboardHook& kh = KeyboardHook::getInstance();

	// modify accents using Insert key
	if (this->settings.input == KU::AccentInput::InsKey)
	{
		kh.setHotkey(VK_INSERT);
	}

	// modify accents using K key
	else
	{
		kh.setHotkey(0x4B);
	}
}

void Klavier::createSettingsFile()
{
	Json::Value default_settings;
	Json::StyledWriter json_writer;

	// set default settings
	default_settings["input"] = "ins";

	QFile settings_file(this->settingsFileName);

	// open settings file for writing
	if (settings_file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream settings_stream(&settings_file);

		settings_stream << json_writer.write(default_settings).c_str();

		settings_file.close();
	}
}

void Klavier::updateSettingsFile()
{
	Json::StyledWriter json_writer;

	QFile settings_file(this->settingsFileName);

	// open settings file for writing
	if (settings_file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream settings_stream(&settings_file);

		// encode Settings struct as a Json::Value object
		settings_stream << json_writer.write(this->settingsEncode(this->settings)).c_str();

		settings_file.close();
	}

	this->applySettings();
}

Json::Value Klavier::settingsEncode(const KU::Settings & settings)
{
	Json::Value encoded;

	encoded["input"] = ((settings.input == KU::AccentInput::InsKey) ? "ins" : "k");

	return encoded;
}

KU::Settings Klavier::settingsDecode(const Json::Value & settings)
{
	KU::Settings decoded;

	decoded.input = ((settings["input"] == string("ins")) ? KU::AccentInput::InsKey : KU::AccentInput::KKey);

	return decoded;
}
