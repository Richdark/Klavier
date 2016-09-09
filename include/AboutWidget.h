#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ui_aboutwidget.h"

class AboutWidget : public QWidget
{
public:
	AboutWidget();
	~AboutWidget();

private:
	Ui::AboutWidget ui;
};

