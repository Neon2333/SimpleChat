#include "SignupForm.h"
#include "LoginForm.h"


SignupForm::SignupForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initForm();
	initEvents();
}

SignupForm::~SignupForm()
{}

void SignupForm::initForm()
{
	this->setWindowTitle("зЂВс");
}

void SignupForm::initEvents()
{
	connect(ui.pushButton_ok, &QPushButton::clicked, this, [=]() {
		//do sign up

		closeEvent(nullptr);
		});

	connect(ui.pushButton_cancel, &QPushButton::clicked, this, [=]() {
			
		closeEvent(nullptr);
		});

}

void SignupForm::closeEvent(QCloseEvent* ev)
{
	Q_UNUSED(ev);

	this->hide();
	LoginForm::self->show();

	//QWidget::closeEvent(ev);
}
