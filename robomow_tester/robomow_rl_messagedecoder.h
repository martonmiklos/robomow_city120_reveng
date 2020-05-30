#ifndef ROBOMOWRL_MESSAGEDECODER_H
#define ROBOMOWRL_MESSAGEDECODER_H

#include <qmath.h>
#include <QMap>

class RobomowRL_MessageDecoder
{
public:
    RobomowRL_MessageDecoder();

    enum MsgProcessState {
        Idle,
        PreambleReceived,
        Data,
        CheckSum
    };

    enum MessageType {
        Unknown = 0,
        LCDContent = 1,
        Unknown_2 = 2,
        Empty_5 = 5,
        Empty_6 = 6
    };


    RobomowRL_MessageDecoder &operator<<(quint8 data);
private:
    QMap<MessageType, int> m_msgTypeSizes;
    MsgProcessState state = Idle;
    MessageType msgCode = Unknown;
    QByteArray dataBuffer;
};

#endif // ROBOMOWRL_MESSAGEDECODER_H
