#include "SignupForm.h"
#include "../inc/LoginForm.h"


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
		std::unique_ptr<AbstractBusiness> business = SendBusinessFactory::CreateBusiness(MsgType::Request, BizCode::Signup);
		Identify identify(ui.lineEdit_username->text().toUtf8(), ui.lineEdit_password->text().toUtf8(), "");
		Data nickname(DataType::Text, ui.lineEdit_nickname->text().length(), ui.lineEdit_nickname->text().toUtf8());
		Forw noforw;
		bool ret = business->SendBusinessProcess(MsgType::Request, BizCode::Signup, identify, nickname, noforw);
			
		if (ret)
		{
			//旋转
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
