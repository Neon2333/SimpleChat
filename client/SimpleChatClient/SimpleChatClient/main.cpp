#include <QtWidgets/QApplication>
#include <../inc/LoginForm.h>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());    //中文显示
    QTranslator* translator = new QTranslator(qApp);
    translator->load(":/qt_zh_CN.qm");  //中文翻译
    a.installTranslator(translator);


    LoginForm loginForm;
    loginForm.show();
    return a.exec();
}
