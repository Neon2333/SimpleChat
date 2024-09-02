#include "../inc/XmlConstructor.h"

/*
        暂时先用拼字符串生成xml
*/

XmlConstructor::XmlConstructor()
{
}

XmlConstructor::~XmlConstructor()
{
}

QByteArray XmlConstructor::ConstructRequestXml(BizCode bizcode, const Identify& identify, const Data& data, const Forw& forw, MsgType msgtype)
{
    assert(!identify.account.isEmpty());

    MD5_STR pwdCipherTmp;
    if (!identify.password.isEmpty())
    {
        //pwdCipher = Md5::getInstance()->cipher(identify.password.data(), identify.password.length());
        MD5StrEncode(identify.password.data(), identify.password.length(), pwdCipherTmp);
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
        .arg(QString::fromUtf8(identify.account))
        .arg(QString(pwdCipherTmp))
        .arg(QString::fromUtf8(identify.token));


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

QByteArray XmlConstructor::ConstructResponseXml(BizCode bizcode, RetCode retcode, const Data& data, MsgType msgtype)
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

QByteArray XmlConstructor::ConstructAckXml(BizCode bizcode, DataType datatype, int receivedDataLen, MsgType msgtype)
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

QByteArray XmlConstructor::ConstructHeartBeatXml()
{
    QString xmltmp = "<msgtype>0</msgtype>";
    return xmltmp.toUtf8();
}

QByteArray XmlConstructor::ConstructSignUpRequestXml(Identify& identify, Data& nickname)
{
    return this->ConstructRequestXml(BizCode::Signup, identify, nickname);
}

QByteArray XmlConstructor::ConstructLoginRequestXml(Identify& identify)
{
    return this->ConstructRequestXml(BizCode::Login, identify);
}

QByteArray XmlConstructor::ConstructLogoutRequestXml(Identify& identify)
{
    return this->ConstructRequestXml(BizCode::Logout, identify);
}

QByteArray XmlConstructor::ConstructChatRequestXml(Identify& identify, const Data& data, const Forw& forw)
{
    assert(data.dataSize != 0 && forw.forwcode != ForwCode::NoForward);
    return this->ConstructRequestXml(BizCode::Chat, identify, data, forw);
}




QByteArray XmlConstructor::ConstructSignUpRequestXml(User& user)
{
    Identify identify = user.GetIdentify();
    Data nickname(DataType::Text, user.Nickname().length(), user.Nickname());
    return ConstructSignUpRequestXml(identify, nickname);
}

QByteArray XmlConstructor::ConstructLoginRequestXml(User& user)
{
    Identify identify = user.GetIdentify();
    return ConstructLoginRequestXml(identify);
}

QByteArray XmlConstructor::ConstructLogoutRequestXml(User& user)
{
    Identify identify = user.GetIdentify();
    return ConstructLogoutRequestXml(identify);
}

QByteArray XmlConstructor::ConstructChatRequestXml(User& user, QByteArray chatMsg, const Forw& forw)
{
    Identify identify = user.GetIdentify();
    Data data(DataType::Text, chatMsg.length(), chatMsg);
    return ConstructChatRequestXml(identify, data, forw);
}












