#include "robomow_rl_messagedecoder.h"

#include <QDebug>

RobomowRL_MessageDecoder::RobomowRL_MessageDecoder()
{
    m_msgTypeSizes[Unknown] = 4;
    m_msgTypeSizes[LCDContent] = 36;
    m_msgTypeSizes[Unknown_2] = 13;
    m_msgTypeSizes[Empty_5] = 4;
    m_msgTypeSizes[Empty_6] = 5;
}

RobomowRL_MessageDecoder& RobomowRL_MessageDecoder::operator<<(quint8 data)
{
    m_dataBuffer.append((char)data);
    if (m_messageState == Idle && m_dataBuffer.count() > 1) {
        if ((m_dataBuffer.at(m_dataBuffer.count() - 2) == 0)
            && ((quint8)m_dataBuffer.at(m_dataBuffer.count() - 1) == 0x80)) {
            m_messageState = PreambleReceived;
        }
    } else if (m_messageState == PreambleReceived) {
        msgCode = (MessageType)m_dataBuffer.at(m_dataBuffer.count() - 1);
        if (!m_msgTypeSizes.contains(msgCode)) {
            qWarning() << "Message with unknonwn (" << msgCode << ") message code received";
        }
        m_messageState = Data;
    } else if (m_messageState == Data) {
        if (m_dataBuffer.count() >= m_msgTypeSizes[msgCode]) {
            quint8 checkSum = 0;
            for (int i = 0; i<m_dataBuffer.count() - 1; i++)
                checkSum += (quint8)m_dataBuffer.at(i);

            if (((quint8)m_dataBuffer.at(m_dataBuffer.count() - 1)) == ((quint8)~checkSum)) {
                m_messageState = Idle;
                if (msgCode == LCDContent) {
                    qWarning() << m_dataBuffer.mid(3, m_dataBuffer.count() - 5);
                } else {
                    qWarning() << m_dataBuffer.toHex();
                }
            } else {
                qWarning() << "Checksum failed!";
            }
            m_dataBuffer.clear();
        }
    }
    return *this;
}
