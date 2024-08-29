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
	Identify m_identify;		//�����֤
	bool m_accountLegal;		//�˻�����Ϸ�
	bool m_isRemeber;			//�Ƿ�����˻�����
	bool m_isAutoLogin;			//�Ƿ��Զ���¼

	QRegExp m_rxUsername;		//������ʽ
	QRegExp m_rxPassword;

	QIcon m_iconLegal;			//ͼ��
	QIcon m_iconIllegal;

	SignupForm* m_signupForm;	//��¼ҳ��
	ServerConfigForm* m_serverConfigForm;

public:
	void initForm();	
	void initEvents();
	static LoginForm* self;		//�洢��������ҳ����з���

signals:
	void notifyLegal(QString str);

private slots:
	void on_pushButton_login_clicked();	//��¼��ť�ۺ���

	void on_notifyLegal(QString str);	//�����˺�����Ϸ�����ʾ

	void on_checkBox_autoLogin_toggled(bool isToggled);	//�Ƿ��Զ���¼

	void on_checkBox_rememberPwd_toggled(bool isToggled);	//�Ƿ��ס����
};

#endif // !LOGINFORM_H
