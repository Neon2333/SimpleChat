#include "LoginForm.h"
#include<QMessageBox>

LoginForm::LoginForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initForm();
	initEvents();
}

LoginForm::~LoginForm()
{}

void LoginForm::initForm()
{
	//ui.pushButton_login->setShortcut(Qt::Key_Enter);
	ui.lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);	
	ui.label_notify->setVisible(false);
	this->accountLegal = false;



	//定义正则
	m_rxUsername.setPattern("^[a-zA-Z0-9_]{6,20}$");
	m_rxPassword.setPattern("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,16}$");

	m_iconLegal.addFile(":/image/ok.png");
	m_iconIllegal.addFile(":/image/error.png");
	
}


void LoginForm::initEvents()
{

	connect(ui.lineEdit_username, &QLineEdit::textChanged, this, [=]() {
		m_identify.account = ui.lineEdit_username->text().toUtf8();
		bool match = m_rxUsername.exactMatch(m_identify.account);

		if (match)
		{
			this->accountLegal = true;
			ui.label_statusUsername->setPixmap(m_iconLegal.pixmap(20, 20));
			ui.label_statusUsername->show();
			emit notifyLegal("");
		}
		else
		{
			this->accountLegal = false;
			ui.label_statusUsername->setPixmap(m_iconIllegal.pixmap(20, 20));
			emit notifyLegal("账号由字母、数字和下划线构成，长度为6-20个字符");
		}
		});

	connect(ui.lineEdit_password, &QLineEdit::textChanged, this, [=]() {
		m_identify.password = ui.lineEdit_password->text().toUtf8();
		bool match = m_rxPassword.exactMatch(m_identify.password);

		if (match)
		{
			this->accountLegal = true;
			ui.label_statusPassword->setPixmap(m_iconLegal.pixmap(20, 20));
			emit notifyLegal("");
		}
		else
		{
			this->accountLegal = false;
			ui.label_statusPassword->setPixmap(m_iconIllegal.pixmap(20, 20));
			emit notifyLegal("密码至少要有1个字母或数字，长度为8-16个字符");
		}
		});

	connect(this, &LoginForm::notifyLegal, this, &LoginForm::on_notifyLegal);
}

void LoginForm::on_pushButton_login_clicked()
{
	if (accountLegal)
	{
		DataEncoder encoder;
		emit notifyLegal("");
		QByteArray loginXml = encoder.ContructLoginRequestXml(m_identify);
		QMessageBox::information(NULL, "debug", loginXml);
	}
	else
	{
		emit notifyLegal("请输入正确的账号或密码");
	}

}

void LoginForm::on_lineEdit_username_textChanged(QString str)
{


}

void LoginForm::on_notifyLegal(QString str)
{
	if (str.isEmpty())
	{
		ui.label_notify->setVisible(false);
		return;
	}

	ui.label_notify->setVisible(true);
	ui.label_notify->setText(str);
}
