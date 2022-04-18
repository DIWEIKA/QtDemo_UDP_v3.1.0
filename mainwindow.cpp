#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Get This PC Name
   localHostName = QHostInfo:: localHostName();
   qDebug() <<"localHostName: "<<localHostName;
   ui->textEdit_Msg->insertPlainText("localHostName: "+localHostName+'\n');

   //Get local IP
   info = QHostInfo::fromName(localHostName);
   strIpAddress  = info.addresses();
   IpAddress =  strIpAddress.back();
   qDebug() << "IpAddress: " << IpAddress;
   ui->textEdit_Msg->insertPlainText("IpAddress: "+IpAddress.toString()+'\n');

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
    RecvAddr.sin_addr.S_un.S_addr = htons(INADDR_ANY); //set Destination IP (suggest 0.0.0.0: 8000)

    //Bind RecvSocket to RecvAddr
   int bdOk = bind(RecvSocket, (SOCKADDR *)&RecvAddr, sizeof(SOCKADDR_IN));

   if(bdOk  == SOCKET_ERROR)
   {
        qDebug() <<"Can't bind Socket !" <<WSAGetLastError()<< endl;
        return;
   }

    //set title
    QString title = QString("Server IP: %1, Port: 8000").arg(IpAddress.toString());
    setWindowTitle(title);

    //init recvdata object
    recvdata = new Recvdata(RecvSocket, ui);

    //Counting 60s
    udpTimer = new QTimer(); //计时1分钟
    udpTimer->setTimerType(Qt::PreciseTimer);//设置定时器对象精确度模式，分辨率为1ms
    udpTimer->start(60000);

    //Every 60s emit a timeout()
    connect(udpTimer,&QTimer::timeout,this,&MainWindow::TimeUpdate);

    //receiving data 有bug！！！！！！！！！
        recvdata->UDPRecieve();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimeUpdate()
{
    qDebug() << "TimeUpdate" << endl;

    ui->textEdit_Msg->insertPlainText("TimeUpdate"+'\n');

    //build new files
    recvdata->changeFileNameOnce();

    //ofstream << CHData
     recvdata->WriteToFilesWith3Channels();

     //close ofstream
    recvdata->closeStream();
}

void MainWindow::on_pushButton_Send_clicked()
{

}

void MainWindow::on_pushButton_Stop_clicked()
{

}


