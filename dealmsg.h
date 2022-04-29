#ifndef DEALMSG_H
#define DEALMSG_H

#include <QThread>
#include <QtNetwork>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class DealMsg;
class  WriteToFiles;

/*QThread DealMsg used for dealing UDP response*/

class DealMsg : public QThread
{
public:
    DealMsg(SOCKET socket);

    void setFlag();
    void resetFlag();

    SOCKET Recvsocket;
    char RecvBuf[];
    int hasRecv;
    QHostAddress clientAddr; //客户端IP
    quint16 clientPort; //客户端port
    shared_ptr<CirQueue<unsigned char>> CHdata2; //测试
    qint64 LenoUDP = 65535*60*10;  //CHdata的长度 最大为9223372036854775807
    qint64 LenoBuf = 65535;
     bool isDone;  //判断线程是否完成

protected:

         void run();

signals:

};

#endif // DEALMSG_H
