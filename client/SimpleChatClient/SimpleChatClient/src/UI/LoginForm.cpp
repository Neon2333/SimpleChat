#include "LoginForm.h"
#include<QMessageBox>

LoginForm::LoginForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//保存窗口对象
	if (self == nullptr)	self = this;
	//创建登录页面
	if (m_signupForm == nullptr)	m_signupForm = new SignupForm();
	//创建服务器配置页面
	if (m_serverConfigForm == nullptr)	m_serverConfigForm = new ServerConfigForm();

	//使用配置文件的ip-port
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
	//参数设定
	//ui.pushButton_login->setShortcut(Qt::Key_Enter);
	this->setWindowTitle("登录");
	ui.lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);	
	ui.label_notify->setVisible(true);

	//定义正则
	m_rxUsername.setPattern("^[a-zA-Z0-9_]{6,20}$");
	m_rxPassword.setPattern("^(?=.*[A-Za-z])(?=.*[0-9])[A-Za-z0-9]{8,16}$");

	//提示icon
	m_iconLegal.addFile(":/image/ok.png");
	m_iconIllegal.addFile(":/image/error.png");


	//读取是否记忆了账号密码、自动登录
	std::unordered_map<std::string, std::string> id = ConfigOper::ReadConfig("./config/user.conf");
	this->m_isRemeber = id["remember"] == "TRUE" ? true : false;
	this->m_isAutoLogin = id["autologin"] == "TRUE" ? true : false;

	//勾选自动登录时，填充账号密码
	if (this->m_isRemeber)
	{
		emit notifyLegal("");	//被保存的账号密码一定合法
		ui.checkBox_rememberPwd->setCheckState(Qt::Checked);
		
		ui.lineEdit_username->setText(id["account"].c_str());		//是否会触发textChanged？会触发！
		//ui.lineEdit_password->setText(id["password"].c_str());	//password是密文，过不了合法性检查
		ui.lineEdit_password->setText("simplechat0");
	}
	//自动登录
	if (this->m_isAutoLogin)
	{
		ui.checkBox_autoLogin->setCheckState(Qt::Checked);
		on_pushButton_login_clicked();
	}


	//尝试连接服务器
	Client::getInstance().m_tcpClient->TryConnectServer(TRYCONNECTCOUNT);	//尝试连接服务器

}



void LoginForm::initEvents()
{
	//检验账号合法性
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
			emit notifyLegal("账号由字母、数字和下划线构成，长度为6-20个字符");
			ui.label_statusUsername->setPixmap(m_iconIllegal.pixmap(20, 20));
		}
		});

	//检验密码合法性
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
			emit notifyLegal("密码至少要有1个字母或数字，长度为8-16个字符");
			ui.label_statusPassword->setPixmap(m_iconIllegal.pixmap(20, 20));
		}
		});

	//合法性显示
	connect(this, &LoginForm::notifyLegal, this, &LoginForm::on_notifyLegal);

	//注册页面显示
	connect(ui.pushButton_signup, &QPushButton::clicked, this, [=]() {
		this->hide();
		m_signupForm->show();
		});

	//服务器配置页面显示
	connect(ui.pushButton_config, &QPushButton::clicked, this, [=]() {
		this->hide();
		m_serverConfigForm->Show();
		});


	//网络是否连接显示
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverConnected, this, [=]() {
		ui.label_notify->setText("已连接服务器");
		ui.pushButton_login->setEnabled(true);
		
		});
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverDisconnected, this, [=]() {
		ui.label_notify->setText("网络未连接");
		ui.pushButton_login->setEnabled(false);

		});


	//通过配置服务器页面重置服务器后，重连服务器
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverIpChanged, this, [=]() {
		Client::getInstance().m_tcpClient->TryConnectServer(TRYCONNECTCOUNT);	//尝试重新连接服务器
		});
	connect(Client::getInstance().m_tcpClient, &TcpClient::serverPortChanged, this, [=]() {
		Client::getInstance().m_tcpClient->TryConnectServer(TRYCONNECTCOUNT);	//尝试重新连接服务器
		});
	//重连次数显示
	connect(Client::getInstance().m_tcpClient, &TcpClient::remainTryCountChanged, this, [=](int remainTryCount) {
		//ui.label_notify->setText(QString("网络未连接,正在重连..（剩余次数：%1）").arg(QString::number(remainTryCount)));
		QMessageBox::information(nullptr, "正在重连..", QString("剩余次数：%1").arg(QString::number(remainTryCount)));
		if(remainTryCount == 0)	
			ui.label_notify->setText("网络未连接");
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

		//记住账号、密码、登陆模式
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
		emit notifyLegal("请输入正确的账号或密码");
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
	//记住账号、密码、登陆模式
	ConfigOper::WriteConfig("./config/user.conf", "autologin", this->m_isAutoLogin ? "TRUE" : "FALSE");
}


void LoginForm::on_checkBox_rememberPwd_toggled(bool isToggled)
{
	//取消记住时清空密码
	if (!isToggled)
		ui.lineEdit_password->clear();

	this->m_isRemeber = isToggled;
	ConfigOper::WriteConfig("./config/user.conf", "remember", this->m_isRemeber ? "TRUE" : "FALSE");

}

void LoginForm::closeEvent(QCloseEvent* ev)
{

	QWidget::closeEvent(ev);
}
