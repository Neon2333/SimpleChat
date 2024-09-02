#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include "ui_LoginForm.h"
#include <QString>
#include <QIntValidator>
#include <QRegExpValidator>
#include "Header.h"
#include "../inc/SignupForm.h"
#include "../inc/ServerConfigForm.h"



class LoginForm : public QWidget
{
	Q_OBJECT

public:
	LoginForm(QWidget *parent = nullptr);
	~LoginForm();

private:
	Ui::LoginFormClass ui;

private:
	Identify m_identify;		//身份验证
	bool m_accountLegal = false;		//账户密码合法
	bool m_isRemeber = false;			//是否记忆账户密码
	bool m_isAutoLogin = false;			//是否自动登录

	QRegExp m_rxUsername;		//正则表达式
	QRegExp m_rxPassword;

	QIcon m_iconLegal;			//图标
	QIcon m_iconIllegal;

	SignupForm* m_signupForm = nullptr;	//登录页面
	ServerConfigForm* m_serverConfigForm = nullptr;

public:
	void initForm();	
	void initEvents();
	static LoginForm* self;		//存储自身，其他页面进行访问

signals:
	void notifyLegal(QString str);

private slots:
	void on_pushButton_login_clicked();	//登录按钮槽函数

	void on_notifyLegal(QString str);	//根据账号密码合法性显示

	void on_checkBox_autoLogin_toggled(bool isToggled);	//是否自动登录

	void on_checkBox_rememberPwd_toggled(bool isToggled);	//是否记住密码

protected:
	void virtual closeEvent(QCloseEvent* ev) override;
};

#endif // !LOGINFORM_H
