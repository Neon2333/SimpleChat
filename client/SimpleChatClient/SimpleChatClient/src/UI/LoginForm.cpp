#include "LoginForm.h"
#include<QMessageBox>

LoginForm::LoginForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//���洰�ڶ���
	if (self == nullptr)	self = this;
	//������¼ҳ��
	if (m_signupForm == nullptr)	m_signupForm = new SignupForm();
	//��������������ҳ��
	if (m_serverConfigForm == nullptr)	m_serverConfigForm = new ServerConfigForm();

	//ʹ�������ļ���ip-port
	Client::getInstance().initTcpClient();

	initEvents();
	initForm();
}

LoginForm::~LoginForm()
{
	if(m_signupForm != nullptr)	delete this->m_signupForm;
	if (m_serverConfigForm != nullptr) delete this->m_serverConfigForm;
}

LoginForm* LoginForm::self = nullptr;


void LoginForm::initForm()
{
	//�����趨
	//ui.pushButton_login->setShortcut(Qt::Key_Enter);
	this->setWindowTitle("��¼");
	ui.lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);	
	ui.label_notify->setVisible(true);

	//��������
	m_rxUsername.setPattern("^[a-zA-Z0-9_]{6,20}$");
	m_rxPassword.setPattern("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,16}$");

	//��ʾicon
	m_iconLegal.addFile(":/image/ok.png");
	m_iconIllegal.addFile(":/image/error.png");


	//��ȡ�Ƿ�������˺����롢�Զ���¼
	std::unordered_map<std::string, std::string> id = ConfigOper::ReadConfig("./config/user.conf");
	this->m_isRemeber = id["remember"] == "TRUE" ? true : false;
	this->m_isAutoLogin = id["autologin"] == "TRUE" ? true : false;

	//��ѡ�Զ���¼ʱ������˺�����
	if (this->m_isRemeber)
	{
		emit notifyLegal("");	//��������˺�����һ���Ϸ�
		ui.checkBox_rememberPwd->setCheckState(Qt::Checked);
		
		ui.lineEdit_username->setText(id["account"].c_str());		//�Ƿ�ᴥ��textChanged���ᴥ����
		//ui.lineEdit_password->setText(id["password"].c_str());	//password�����ģ������˺Ϸ��Լ��
		ui.lineEdit_password->setText("simplechat0");
	}
	//�Զ���¼
	if (this->m_isAutoLogin)
	{
		ui.checkBox_autoLogin->setCheckState(Qt::Checked);
		on_pushButton_login_clicked();
	}


	//�������ӷ�����
	Client::getInstance().m_tcpClient->TryConnectServer(TRYCONNECTCOUNT);	//�������ӷ�����

}



void LoginForm::initEvents()
{
	//�����˺źϷ���
	connect(ui.lineEdit_username, &QLineEdit::textChanged, this, [=]() {
		m_identify.account = ui.lineEdit_username->text().toUtf8();
		bool match = m_rxUsername.exactMatch(m_identify.account);

		if (match)
		{
			emit notifyLegal("");
			ui.label_statusUsername->setPixmap(m_iconLegal.pixmap(20, 20));
		}
		else
		{
			emit notifyLegal("�˺�����ĸ�����ֺ��»��߹��ɣ�����Ϊ6-20���ַ�");
			ui.label_statusUsername->setPixmap(m_iconIllegal.pixmap(20, 20));
		}
		});

	//��������Ϸ���
	connect(ui.lineEdit_password, &QLineEdit::textChanged, this, [=]() {
		m_identify.password = ui.lineEdit_password->text().toUtf8();
		bool match = m_rxPassword.exactMatch(m_identify.password);

		if (match)
		{
			emit notifyLegal("");
			ui.label_statusPassword->setPixmap(m_iconLegal.pixmap(20, 20));
		}
		else
		{
			emit notifyLegal("��������Ҫ��1����ĸ�����֣�����Ϊ8-16���ַ�");
			ui.label_statusPassword->setPixmap(m_iconIllegal.pixmap(20, 20));
		}
		});

	//�Ϸ�����ʾ
	connect(this, &LoginForm::notifyLegal, this, &LoginForm::on_notifyLegal);

	//ע��ҳ����ʾ
	connect(ui.pushButton_signup, &QPushButton::clicked, this, [=]() {
		this->hide();
		m_signupForm->show();
		});

	//����������ҳ����ʾ
	connect(ui.pushButton_config, &QPushButton::clicked, this, [=]() {
		this->hide();
		m_serverConfigForm->Show();
		});


	//�����Ƿ�������ʾ
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverConnected, this, [=]() {
		ui.label_notify->setText("�����ӷ�����");
		ui.pushButton_login->setEnabled(true);
		
		});
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverDisconnected, this, [=]() {
		ui.label_notify->setText("����δ����");
		ui.pushButton_login->setEnabled(false);

		});


	//ͨ�����÷�����ҳ�����÷�����������������
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverIpChanged, this, [=]() {
		Client::getInstance().m_tcpClient->TryConnectServer(TRYCONNECTCOUNT);	//�����������ӷ�����
		});
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverPortChanged, this, [=]() {
		Client::getInstance().m_tcpClient->TryConnectServer(TRYCONNECTCOUNT);	//�����������ӷ�����
		});
	//����������ʾ
	connect(Client::getInstance().m_tcpClient, &TcpClient::remainTryCountChanged, this, [=](int remainTryCount) {
		//ui.label_notify->setText(QString("����δ����,��������..��ʣ�������%1��").arg(QString::number(remainTryCount)));
		QMessageBox::information(nullptr, "��������..", QString("ʣ�������%1").arg(QString::number(remainTryCount)));
		if(remainTryCount == 0)	
			ui.label_notify->setText("����δ����");
		});
}

void LoginForm::on_pushButton_login_clicked()
{
	if (m_accountLegal)
	{
		XmlConstructor xmlConstructor;
		emit notifyLegal("");
		QByteArray loginXml = xmlConstructor.ConstructLoginRequestXml(m_identify);
		qDebug() << loginXml;

		bool loginSucceed = true;

		//��ס�˺š����롢��½ģʽ
		if (m_isRemeber && loginSucceed)
		{
			std::unordered_map<std::string, std::string> id;
			id.insert(std::make_pair("account", m_identify.account));
			MD5_STR pwdCipher;
			SSLHelper::MD5StrEncode(m_identify.password.data(), m_identify.password.length(), pwdCipher);
			id.insert(std::make_pair("password", std::string(pwdCipher, 32)));
			id.insert(std::make_pair("autologin", this->m_isAutoLogin ? "TRUE" : "FALSE"));
			id.insert(std::make_pair("remember", this->m_isRemeber ? "TRUE" : "FALSE"));
			ConfigOper::WriteConfig("./config/user.conf", id, ConfigWriteType::Cover);
		}
	}
	else
	{
		emit notifyLegal("��������ȷ���˺Ż�����");
	}

}


void LoginForm::on_notifyLegal(QString str)
{
	if (str.isEmpty())
	{
		m_accountLegal = true;
		ui.label_notify->setText("");
		return;
	}

	m_accountLegal = false;
	ui.label_notify->setVisible(true);
	ui.label_notify->setText(str);
}

void LoginForm::on_checkBox_autoLogin_toggled(bool isToggled)
{
	this->m_isAutoLogin = isToggled;
	//��ס�˺š����롢��½ģʽ
	ConfigOper::WriteConfig("./config/user.conf", "autologin", this->m_isAutoLogin ? "TRUE" : "FALSE");
}


void LoginForm::on_checkBox_rememberPwd_toggled(bool isToggled)
{
	//ȡ����סʱ�������
	if (!isToggled)
		ui.lineEdit_password->clear();

	this->m_isRemeber = isToggled;
	ConfigOper::WriteConfig("./config/user.conf", "remember", this->m_isRemeber ? "TRUE" : "FALSE");

}

void LoginForm::closeEvent(QCloseEvent* ev)
{

	QWidget::closeEvent(ev);
}
