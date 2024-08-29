#ifndef SERVERCONFIGFORM_H
#define SERVERCONFIGFORM_H

#include <QWidget>
#include "ui_ServerConfigForm.h"

class ServerConfigForm : public QWidget
{
	Q_OBJECT

public:
	ServerConfigForm(QWidget *parent = nullptr);
	~ServerConfigForm();

private:
	Ui::ServerConfigFormClass ui;

private:
	void initForm();
	void initEvents();

protected:
	void virtual closeEvent(QCloseEvent* ev);
};

#endif // !SERVERCONFIGFORM_H