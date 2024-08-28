#pragma once

#include <QWidget>
#include "ui_LoginForm.h"
#include <QString>
#include <QIntValidator>
#include <QRegExpValidator>
#include "DataEncoder.h"
#include "Header.h"


class LoginForm : public QWidget
{
	Q_OBJECT

public:
	LoginForm(QWidget *parent = nullptr);
	~LoginForm();

private:
	Ui::LoginFormClass ui;

private:
	bool accountLegal;	//账户密码合法
	Identify m_identify;	//账户密码

	QRegExp m_rxUsername;	
	QRegExp m_rxPassword;

	QIcon m_iconLegal;
	QIcon m_iconIllegal;


public:
	void initForm();
	void initEvents();

signals:
	void notifyLegal(QString str);

private slots:
	void on_pushButton_login_clicked();

	void on_lineEdit_username_textChanged(QString str);

	void on_notifyLegal(QString str);
};
