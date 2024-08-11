#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "TcpClient.h"
#include <assert.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();
    void initEvents();

private:
    Ui::MainWindowClass ui;
    TcpClient* m_tcpclient;

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_send_clicked();
    void onConnected();
    void onDisconnected();
    void onDataSended(qint64 len);
    void onDataRecved(QString msg);

};
