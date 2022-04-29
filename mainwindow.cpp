#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init Socket
    initRecvSocket();

    //set Local Message
    setLocalMsg();

    //Counting 60s
    udpTimer = new QTimer();
    udpTimer->setTimerType(Qt::PreciseTimer);//设置定时器对象精确度模式，分辨率为1ms
    isTimeUpdate = false;
    udpTimer->start(60000);

    dealMsg  = new DealMsg(RecvSocket);

    writeToFiles = new WriteToFiles(dealMsg);

    OpenDealMsgThread();

    //Every time dealMsg is finished, connect dealMsgFinshedSlot()
    connect(dealMsg,&QThread::finished,this,&MainWindow::FinishDealMsgThread);

    //Every 60s emit a timeout(), connect OpenWriteToFilesThread
    connect(udpTimer,&QTimer::timeout,this,&MainWindow::OpenWriteToFilesThread);

    //Every time dealMsg is finished, connect dealMsgFinshedSlot()
    connect(writeToFiles,&QThread::finished,this,&MainWindow::FinishWriteToFilesThread);

 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLocalMsg()
{
    //获取本机的计算机名
   QString localHostName = QHostInfo:: localHostName();
   qDebug() <<"localHostName: "<<localHostName<<endl;

   ui->textEdit_Msg->insertPlainText("localHostName: "+localHostName+'\n');

   //获取本机IP
   QHostInfo info = QHostInfo::fromName(localHostName);
   QList<QHostAddress> strIpAddress  = info.addresses();
   QHostAddress IpAddress =  strIpAddress.back();
   qDebug() << "IpAddress: " << IpAddress<<endl;
   qDebug()<<"--------------------------"<<endl;

   ui->textEdit_Msg->insertPlainText("IpAddress: "+IpAddress.toString()+'\n');

   //设置窗口的标题
   QString title = QString("Server IP: %1, Port: 7000").arg(IpAddress.toString());
   setWindowTitle(title);
}

void MainWindow::OpenDealMsgThread()
{
    dealMsg->setFlag();

    //If dealMsg is Running, wait until it finished
       if(dealMsg->isRunning())
           dealMsg->wait();

    //run DealMsg Thread
    dealMsg->start();

    ui->textEdit_Msg->insertPlainText("Pending...");
}

void MainWindow::FinishDealMsgThread()
{
    //quit Thread
    dealMsg->quit();

    dealMsg->wait();

}

void MainWindow::OpenWriteToFilesThread()
{
//    //first quit dealMsg Thread
//    dealMsg->resetFlag();

    //then writeToFiles->run()
    writeToFiles->start();
}

void MainWindow::FinishWriteToFilesThread()
{
    //quit Thread
    writeToFiles->quit();

    writeToFiles->wait();

}


void MainWindow::initRecvSocket()
{
    //Startup Winsock
    int wsOk =  WSAStartup(MAKEWORD(2,2),&wsaData);

    if(wsOk != 0)
    {
            qDebug() <<"Can't start Winsock !" << endl;
            return;
    }

    //init RecvSocket
    RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(RecvSocket == INVALID_SOCKET)
    {
        qDebug() <<"Socket established failed !" << endl;
        return;
    }

    //Config RecvAddr
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(7000); //set Destination port
    RecvAddr.sin_addr.S_un.S_addr = htons(INADDR_ANY); //set Destination IP
    qDebug() << "port: 7000 " << endl;
    ui->textEdit_Msg->insertPlainText("port:  7000"+'\n');

    //Bind RecvSocket to RecvAddr
   int bdOk = bind(RecvSocket, (SOCKADDR *)&RecvAddr, sizeof(SOCKADDR_IN));

   if(bdOk  == SOCKET_ERROR)
   {
        qDebug() <<"Can't bind Socket !" <<WSAGetLastError()<< endl;
        return;
   }
}

