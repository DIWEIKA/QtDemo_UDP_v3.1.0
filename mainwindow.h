#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <recvdata.h>
#include <QtDebug>

#include <winsock2.h>
#include <windows.h>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Recvdata; //使用前向声明


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
    QString localHostName;
    QHostInfo info;
    QList<QHostAddress> strIpAddress;
    QHostAddress IpAddress;
    WSADATA wsaData;
    sockaddr_in RecvAddr;
    SOCKET RecvSocket;

    Recvdata *recvdata;

    QUdpSocket *udpSocket; //udp pointer
    QTimer* udpTimer;

    bool isStopSend;

private slots:
    void on_pushButton_Send_clicked();
    void on_pushButton_Stop_clicked();
    void TimeUpdate();

private:

    bool isTimeUpdate;
};
#endif // MAINWINDOW_H
