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
	this->setWindowTitle("ע��");
}

void SignupForm::initEvents()
{
	//ע�ᰴť�¼�
	connect(ui.pushButton_ok, &QPushButton::clicked, this, [=]() {
		DoSignUp doSignUp;
		RetCodeSignUp retcode = doSignUp.SignUp(ui.lineEdit_username->text(), ui.lineEdit_password->text(), ui.lineEdit_nickname->text());
		switch (retcode)
		{
		case RetCodeSignUp::Succeed:
			QMessageBox::information(nullptr, "info", "ע��ɹ���");
			break;
		case RetCodeSignUp::Failed:
			QMessageBox::information(nullptr, "info", "ע��ʧ�ܣ�");
			break;
		case RetCodeSignUp::AccountExisted:
			QMessageBox::information(nullptr, "info", "�˺��Ѵ���..");
			break;
		default:
			break;
		}

		closeEvent(nullptr);
		});

	//ȡ����ť�¼�
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
