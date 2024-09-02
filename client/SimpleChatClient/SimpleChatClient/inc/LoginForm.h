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
	bool m_accountLegal = false;		//�˻�����Ϸ�
	bool m_isRemeber = false;			//�Ƿ�����˻�����
	bool m_isAutoLogin = false;			//�Ƿ��Զ���¼

	QRegExp m_rxUsername;		//������ʽ
	QRegExp m_rxPassword;

	QIcon m_iconLegal;			//ͼ��
	QIcon m_iconIllegal;

	SignupForm* m_signupForm = nullptr;	//��¼ҳ��
	ServerConfigForm* m_serverConfigForm = nullptr;

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

protected:
	void virtual closeEvent(QCloseEvent* ev) override;
};

#endif // !LOGINFORM_H
