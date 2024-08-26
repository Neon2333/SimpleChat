#include "../inc/DataEncoder.h"

/*
        暂时先用拼字符串生成xml
*/

DataEncoder::DataEncoder()
{
}

DataEncoder::~DataEncoder()
{
}

QByteArray DataEncoder::ConstructRequestXml(BizCode bizcode, const Identify& identify, const Data& data, const Forw& forw, MsgType msgtype)
{
    assert(!identify.account.isEmpty());

    QByteArray pwdEncode;
    if (!identify.password.isEmpty())
    {
        pwdEncode = Md5::getInstance()->encode(identify.password.toUtf8().data(), identify.password.length());
    }

    QString xmltmp = QString(
        "<msgtype>1</msgtype>\
        <bizcode>%1</bizcode>\
        <identify>\
        <account>%2</account>\
        <password>%3</password>\
        <token>%4</token>\
        </identify>")
        .arg(QString::number(static_cast<int>(bizcode)))
        .arg(identify.account)
        .arg(QString::fromUtf8(pwdEncode))
        .arg(identify.token);


    if (data.dataSize != 0)
    {
        QString databodytmp;
        if (data.dataType != DataType::Text)
        {
            databodytmp = QString::fromUtf8(data.databody.toBase64());
            
        }
        else
        {
            databodytmp = QString::fromUtf8(data.databody);
        }
        xmltmp += QString("<data><datatpye>%1</datatype><datasize>%2</datasize><databody>%3</databody></data>")
            .arg(static_cast<int>(data.dataType))
            .arg(QString::number(data.dataSize))
            .arg(databodytmp);
    }
    
    if (forw.forwcode != ForwCode::NoForward)
    {
        xmltmp += QString("<forw><forwcode>%1</forwcode><rececount>%2</rececount>")
            .arg(static_cast<int>(forw.forwcode))
            .arg(forw.receiveCount);
        for (int ii = 0; ii < forw.receiveCount; ++ii)
        {
            xmltmp += QString("<receiver%1>%2</receiver%3>")
                .arg(QString::number(ii))
                .arg(forw.receivers.at(ii))
                .arg(QString::number(ii));
        }
        xmltmp += QString("</forw>");
    }

    return xmltmp.toUtf8();
}

QByteArray DataEncoder::ConstructResponseXml(BizCode bizcode, RetCode retcode, const Data data, MsgType msgtype)
{
    QString xmltmp = QString("<msgtype>%1</msgtype><bizcode>%2</bizcode><retcode>%3</retcode>")
        .arg(static_cast<int>(MsgType::Response))
        .arg(static_cast<int>(bizcode))
        .arg(static_cast<int>(retcode));

    if (data.dataSize != 0)
    {
        QString databodytmp;
        if (data.dataType != DataType::Text)
        {
            databodytmp = QString::fromUtf8(data.databody.toBase64());
        }
        else
        {
            databodytmp = QString::fromUtf8(data.databody);
        }
        xmltmp += QString("<data><datatpye>%1</datatype><datasize>%2</datasize><databody>%3</databody></data>")
            .arg(static_cast<int>(data.dataType))
            .arg(QString::number(data.dataSize))
            .arg(databodytmp);
    }

    return xmltmp.toUtf8();
}

QByteArray DataEncoder::ConstructAckXml(BizCode bizcode, DataType datatype, int receivedDataLen, MsgType msgtype)
{
    QString xmltmp = QString("<msgtype>ack</msgtype>\
        <bizcode>%1</bizcode>\
        <datatype>%2</datatype>\
        <receivesize>%3</recevivesize>")
        .arg(QString::number(static_cast<int>(bizcode)))
        .arg(QString::number(static_cast<int>(datatype)))
        .arg(QString::number(static_cast<int>(receivedDataLen)));

    return xmltmp.toUtf8();
}

QByteArray DataEncoder::ConstructHeartBeatXml()
{
    QString xmltmp = "<msgtype>0</msgtype>";
    return xmltmp.toUtf8();
}

QByteArray DataEncoder::ConstructSignUpRequestXml(Identify& identify)
{
    return this->ConstructRequestXml(BizCode::Signup, identify);
}

QByteArray DataEncoder::ContructLoginRequestXml(Identify& identify)
{
    return this->ConstructRequestXml(BizCode::Login, identify);
}

QByteArray DataEncoder::ConstructLogoutRequestXml(Identify& identify)
{
    return this->ConstructRequestXml(BizCode::Logout, identify);
}

QByteArray DataEncoder::ConstructChatRequestXml(Identify& identify, ForwCode forwcode, const Data& data, const Forw& forw)
{
    assert(data.dataSize != 0 && forw.forwcode != ForwCode::NoForward);
    return this->ConstructRequestXml(BizCode::Chat, identify, data, forw);
}












