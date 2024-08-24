#include "../inc/DataEncoder.h"

DataEncoder::DataEncoder()
{
}

DataEncoder::~DataEncoder()
{
}

QByteArray DataEncoder::ConstructRequestXml(BizCode bizcode, ForwCode forwcode, const QString& account, const QString& password, DataType datatype, const QByteArray& databody, const std::vector<QString>& receivers)
{
    /*
        暂时先用拼字符串生成xml
    */
    assert(databody != nullptr);

    QByteArray pwdtmp = Md5::md5()->encode(password.toUtf8().data(), password.length());
    
    QString databodytmp;
    if (datatype == DataType::image || datatype == DataType::file)
    {
        databodytmp = QString::fromUtf8(databody.toBase64());
    }
    else
    {
        databodytmp = QString::fromUtf8(databody);
    }

    QString xmltmp = QString("<msgtype>request</msgtype>\
        <bizcode>%1</bizcode>\
        <forwcode>%2</forwcode>\
        <account>%3</account>\
        <password>%4</password>\
        <datatype>%5</datatype>\
        <databody>%6</databody>")
        .arg(QString::number(static_cast<int>(bizcode)))
        .arg(QString::number(static_cast<int>(forwcode)))
        .arg(account)
        .arg(QString::fromUtf8(pwdtmp))
        .arg(QString::number(static_cast<int>(datatype)))
        .arg(databodytmp);


    switch (forwcode)
    {
    case ForwCode::forwardtoone:
        assert(receivers.size() != 1);
        xmltmp += QString("<receiver>%1</receiver>").arg(receivers.at(0));
        break;
    case ForwCode::forwardtogroup:
        assert(receivers.size() > 1);
        xmltmp += QString("<receivercount></receivercount>").arg(QString::number(receivers.size()));
        for (int ii = 0; ii < receivers.size(); ++ii)
        {
            xmltmp += QString("<receiver%1>%2</receiver%1>").arg(QString::number(ii + 1)).arg(receivers.at(ii));
        }

    default:
        break;
    }
    
    

    return xmltmp.toUtf8();
}

QByteArray DataEncoder::ConstructResponseXml(BizCode bizcode, const QString& account, RetCode retcode, DataType datatype, const QByteArray& databody)
{
    if (databody == nullptr)   return nullptr;

    QString databodytmp;

    if (datatype == DataType::image || datatype == DataType::file)
    {
        databodytmp = QString::fromUtf8(databody.toBase64());
    }
    else
    {
        databodytmp = QString::fromUtf8(databody);
    }

    QString xmltmp = QString("<msgtype>response</msgtype>\
        <bizcode>%1</bizcode>\
        <account>%2</account>\
        <retcode>%3</retcode>\
        <datatype>%4</datatype>\
        <databody>%5</databody>")
        .arg(QString::number(static_cast<int>(bizcode)))
        .arg(account)
        .arg(QString::number(static_cast<int>(retcode)))
        .arg(QString::number(static_cast<int>(datatype)))
        .arg(databodytmp);

    return xmltmp.toUtf8();
}

QByteArray DataEncoder::ConstructAckXml(BizCode bizcode, const QString& account, DataType datatype, int receivedDatalen)
{
    QString xmltmp = QString("<msgtype>ack</msgtype>\
        <bizcode>%1</bizcode>\
        <account>%2</account>\
        <datatype>text</datatype>\
        <databody>%3</databody>")
        .arg(QString::number(static_cast<int>(bizcode)))
        .arg(account)
        .arg(QString::number(receivedDatalen));

    return xmltmp.toUtf8();
}

QByteArray DataEncoder::ConstructHeartBeatXml()
{
    QString xmltmp = "<msgtype>heartbeat</msgtype>";
}

QByteArray DataEncoder::ConstructSignUpRequestXml(const QString& account, const QString& password)
{
    return this->ConstructRequestXml(BizCode::signup, ForwCode::noforward, account, password, DataType::text, "");
}

QByteArray DataEncoder::ContructLoginRequestXml(const QString& account, const QString& password)
{
    return this->ConstructRequestXml(BizCode::login, ForwCode::noforward, account, password, DataType::text, "");
}

QByteArray DataEncoder::ConstructLogoutRequestXml(const QString& account, const QString& password)
{
    return this->ConstructRequestXml(BizCode::logout, ForwCode::noforward, account, password, DataType::text, "");
}

QByteArray DataEncoder::ConstructChatRequestXml(const QString& account, const QString& password, ForwCode forwcode, QByteArray databody, const std::vector<QString>& receivers)
{
    return this->ConstructRequestXml(BizCode::chat, forwcode, account, password, DataType::text, databody, receivers);
}












