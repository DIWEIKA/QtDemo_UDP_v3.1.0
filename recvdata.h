#ifndef RECVDATA_H
#define RECVDATA_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QQueue>
#include "CirQueue.h"
#include <memory>
#include <fstream>
#include <QtNetwork>
#include <sstream>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <winsock2.h>
#include <ws2tcpip.h>


 typedef unsigned char BYTE;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow;

class Recvdata : public QObject
{
public:
    Recvdata(SOCKET socket, Ui::MainWindow *ui);
    ~Recvdata();
    void readDatagram();//读取udp信息
    void getDatafromBufToCHdata();
    void changeFileNameOnce();//初次生成存储文件名
    void WriteToFilesWith3Channels();
    void closeStream();
    void UDPRecieve();
    void CloseUDP();

    Ui::MainWindow *UI;
    SOCKET Recvsocket;

    qint64 LenoUDP = 1366*60000;  //CHdata的长度 最大为9223372036854775807
    string saveFolder;//存储目录（文件夹）
    QString saveFilename1; //CH1存储文件名
    QString saveFilename2;
    QString saveFilename3;
    QString file1;
    QString file2;
    QString file3;
    ofstream outfile1;//CH1
    ofstream outfile2;
    ofstream outfile3;
    QDateTime dateTime; //当前系统时间
    sockaddr_in clientAddr; //客户端地址
    quint16 clientPort; //客户端端口号
    QTimer* udpTimer; //定时器 用来计时1分钟
    shared_ptr<CirQueue<float>> CHdata; //存放Channel数据的容器
    shared_ptr<CirQueue<char>> CHdata2; //测试
    char usCHDATA;
    qint64 LenoBuf;
    char RecvBuf[];
    int hasRecv;
    int PeakNum = 31;//峰值数

public slots:


private slots:


private:


};

#endif // RECVDATA_H
