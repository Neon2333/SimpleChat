#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <../inc/LoginForm.h>
#include "inc/Client.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());    //中文显示
    QTranslator* translator = new QTranslator(qApp);
    translator->load(":/qt_zh_CN.qm");  //中文翻译
    a.installTranslator(translator);


    LoginForm loginForm;
    loginForm.show();

    //主界面里，异步通信。login、signup都同步通信。
    //QObject::connect(Client::m_tcpClient, &TcpClient::dataSended, this, &MainWindow::onDataSended);
    //QObject::connect(Client::m_tcpClient, &TcpClient::dataRecved, this, &MainWindow::onDataRecved);
    
    return a.exec();
}
