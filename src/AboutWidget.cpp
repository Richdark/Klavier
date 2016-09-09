#include "include/AboutWidget.h"

AboutWidget::AboutWidget()
{
	this->ui.setupUi(this);

	// plain widget with a title and a close button
	this->setWindowFlags(Qt::Widget | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

	// add app icon
	this->ui.icon->setPixmap(QPixmap(":/images/icon.png"));

	// enable label hyperlinks
	this->ui.label->setOpenExternalLinks(true);
	this->ui.contacts_right->setOpenExternalLinks(true);
}

AboutWidget::~AboutWidget()
{
}
