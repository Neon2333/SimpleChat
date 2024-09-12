#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QWidget>
#include "ui_SignupForm.h"
#include "Header.h"
#include "SendBusinessFactory.h"

class SignupForm : public QWidget
{
	Q_OBJECT

public:
	SignupForm(QWidget *parent = nullptr);
	~SignupForm();
private:
	Ui::SignupFormClass ui;

private:
	void initForm();
	void initEvents();

protected:
	void virtual closeEvent(QCloseEvent* ev) override;
};

#endif // !SIGNUPFORM_H
