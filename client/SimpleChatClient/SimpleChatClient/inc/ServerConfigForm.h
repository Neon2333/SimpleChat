#ifndef SERVERCONFIGFORM_H
#define SERVERCONFIGFORM_H

#include <QWidget>
#include "ui_ServerConfigForm.h"
#include "../inc/Client.h"


class ServerConfigForm : public QWidget
{
	Q_OBJECT

public:
	ServerConfigForm(QWidget *parent = nullptr);
	~ServerConfigForm();

	void Show();

private:
	Ui::ServerConfigFormClass ui;

private:
	void initForm();
	void initEvents();

protected:
	void virtual closeEvent(QCloseEvent* ev) override;

signals:
	void serverConfigReset();
};

#endif // !SERVERCONFIGFORM_H