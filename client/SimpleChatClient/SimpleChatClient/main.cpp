#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <../inc/LoginForm.h>
#include "inc/Client.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());    //������ʾ
    QTranslator* translator = new QTranslator(qApp);
    translator->load(":/qt_zh_CN.qm");  //���ķ���
    a.installTranslator(translator);


    LoginForm loginForm;
    loginForm.show();

    //��������첽ͨ�š�login��signup��ͬ��ͨ�š�
    //QObject::connect(Client::m_tcpClient, &TcpClient::dataSended, this, &MainWindow::onDataSended);
    //QObject::connect(Client::m_tcpClient, &TcpClient::dataRecved, this, &MainWindow::onDataRecved);
    
    return a.exec();
}
