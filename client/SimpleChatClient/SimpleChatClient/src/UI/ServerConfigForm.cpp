#include "ServerConfigForm.h"
#include "../inc/LoginForm.h"


ServerConfigForm::ServerConfigForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initEvents();
	initForm();
}

ServerConfigForm::~ServerConfigForm()
{}

void ServerConfigForm::initForm()
{
	this->setWindowTitle("·þÎñÆ÷ÅäÖÃ");

}

void ServerConfigForm::initEvents()
{
	connect(ui.pushButton_ok, &QPushButton::clicked, this, [=]() {
		//do set server configuration

		closeEvent(nullptr);
		});

	connect(ui.pushButton_cancel, &QPushButton::clicked, this, [=]() {

		closeEvent(nullptr);
		});


}

void ServerConfigForm::closeEvent(QCloseEvent* ev)
{
	Q_UNUSED(ev);

	this->hide();
	LoginForm::self->show();
}
