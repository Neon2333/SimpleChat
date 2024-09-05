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

void ServerConfigForm::Show()
{
	this->show();
	ui.lineEdit_host->setText(Client::m_tcpClient->ServerIp());
	ui.lineEdit_port->setText(QString::number(Client::m_tcpClient->Port()));
}

void ServerConfigForm::initForm()
{
	this->setWindowTitle("服务器配置");
	
}

void ServerConfigForm::initEvents()
{
	//设定ip-port
	connect(ui.pushButton_ok, &QPushButton::clicked, this, [=]() {
		Client::setTcpClient(ui.lineEdit_host->text(), ui.lineEdit_port->text().toInt());
		emit serverConfigReset();
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
