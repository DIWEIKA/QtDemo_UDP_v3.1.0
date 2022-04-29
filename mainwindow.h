#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QtNetwork>
#include <recvdata.h>
#include <QtDebug>
#include <winsock2.h>
#include <windows.h>
#include <dealmsg.h>
#include <writetofiles.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Recvdata; //使用前向声明
class Senddata;
class DealMsg;
class  WriteToFiles;

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

    QTimer* udpTimer;
    DealMsg* dealMsg;
    WriteToFiles* writeToFiles;
    bool isStopSend;

    void setLocalMsg();
    void OpenDealMsgThread();
    void OpenWriteToFilesThread();
    void stopThread();
    void initRecvSocket();

private slots:
    void FinishDealMsgThread();
    void FinishWriteToFilesThread();


private:
    bool isTimeUpdate;
};
#endif // MAINWINDOW_H
