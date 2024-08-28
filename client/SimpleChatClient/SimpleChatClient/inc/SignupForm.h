#pragma once

#include <QWidget>
#include "ui_SignupForm.h"
#include "Header.h"

class SignupForm : public QWidget
{
	Q_OBJECT

public:
	SignupForm(QWidget *parent = nullptr);
	~SignupForm();

private:
	Ui::SignupFormClass ui;
};
