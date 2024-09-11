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
	this->setWindowTitle("注册");
}

void SignupForm::initEvents()
{
	//注册按钮事件
	connect(ui.pushButton_ok, &QPushButton::clicked, this, [=]() {
		DoSignUp doSignUp;
		RetCodeSignUp retcode = doSignUp.SignUp(ui.lineEdit_username->text(), ui.lineEdit_password->text(), ui.lineEdit_nickname->text());
		switch (retcode)
		{
		case RetCodeSignUp::Succeed:
			QMessageBox::information(nullptr, "info", "注册成功！");
			break;
		case RetCodeSignUp::Failed:
			QMessageBox::information(nullptr, "info", "注册失败！");
			break;
		case RetCodeSignUp::AccountExisted:
			QMessageBox::information(nullptr, "info", "账号已存在..");
			break;
		default:
			break;
		}

		closeEvent(nullptr);
		});

	//取消按钮事件
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
