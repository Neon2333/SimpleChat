#include <QtWidgets/QApplication>
#include <../inc/LoginForm.h>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());    //������ʾ
    QTranslator* translator = new QTranslator(qApp);
    translator->load(":/qt_zh_CN.qm");  //���ķ���
    a.installTranslator(translator);


    LoginForm loginForm;
    loginForm.show();
    return a.exec();
}
