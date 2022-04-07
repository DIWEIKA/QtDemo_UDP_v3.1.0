#ifndef SENDDATA_H
#define SENDDATA_H

#include <fstream>
#include <sstream>
#include <QMainWindow>
#include <memory>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <winsock2.h>

class Senddata  : public QObject
{
public:
    Senddata(SOCKET socket, Ui::MainWindow *ui);
    ~Senddata();
    void ReadFromFiles(); //ifStream >> sendData
    void getConfig();  //sendData>>msgbuf
    void writeDatagram(); //msgbuf>>UDP
    void  closeUDP();

    Ui::MainWindow *UI;
    SOCKET Sendsocket;
    ifstream infile; //本地待发送数据
    QString file; //本地文件目录
    QString saveFolder;
    string sendData; //发送一包UDP数据，超过8192Byte会丢包，超过65535Byte会无法发送
    QByteArray msgbuf;
    QString DestIP;
    qint16 DestPort;
    sockaddr_in RecvAddr;//服务器地址
    quint16 RecvPort;//服务器端口号
    int Lenobuf; //length of msgbuf
};

#endif // SENDDATA_H
