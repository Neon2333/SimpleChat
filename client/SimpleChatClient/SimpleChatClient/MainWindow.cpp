#include "MainWindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    init();
    initEvents();
}

MainWindow::~MainWindow()
{}

void MainWindow::init()
{
    //从配置文件中读取，可设定
    m_tcpclient = new TcpClient();

    ui.statusBar->showMessage("disconnected..");
    //listwidget->addItem(msg.left(datagram.size()));

}

void MainWindow::initEvents()
{
    connect(m_tcpclient, &TcpClient::serverConnected, this, &MainWindow::onConnected);
    connect(m_tcpclient, &TcpClient::serverDisconnected, this, &MainWindow::onDisconnected);
    connect(m_tcpclient, &TcpClient::dataSended, this, &MainWindow::onDataSended);
    connect(m_tcpclient, &TcpClient::dataRecved, this, &MainWindow::onDataRecved);

}

void MainWindow::on_pushButton_connect_clicked()
{
    assert(m_tcpclient != nullptr);
    
    if (this->ui.lineEdit_serverIP->text().isEmpty() || this->ui.lineEdit_serverPort->text().isEmpty())
    {
        QMessageBox::information(this, "info", "IP或端口设置有误..");
    }
    m_tcpclient->ConnectToServer(this->ui.lineEdit_serverIP->text(), this->ui.lineEdit_serverPort->text().toUInt());
}

void MainWindow::on_pushButton_send_clicked()
{
    assert(m_tcpclient != nullptr);
    
    if (!this->ui.lineEdit_enterMsg->text().isEmpty() && m_tcpclient->IsConnected())
    {
        QString msgtmp = QString("<bizcode>2</bizcode><forwcode>1</forwcode><message>%1</message>").arg(this->ui.lineEdit_enterMsg->text());
        bool ret = m_tcpclient->Send(msgtmp.toUtf8(), 0);
    }
}

void MainWindow::onConnected()
{
    ui.statusBar->showMessage("connected..");
}

void MainWindow::onDisconnected()
{
    ui.statusBar->showMessage("disconnected..");
}

void MainWindow::onDataSended(qint64 len)
{
    ui.statusBar->showMessage(QString("send: %1 Bytes").arg(len));
}

void MainWindow::onDataRecved(QString msg)
{
    ui.listWidget_msg->addItem(msg);
}


