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
    RecvSocket = socket(AF_INET, SOCK_DGRAM, 0);

    //Config RecvAddr
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(8000); //Client port 8000
    RecvAddr.sin_addr.S_un.S_addr = inet_addr( "127.0.0.1"); //Client IP

    //Bind RecvSocket to RecvAddr
   int bdOk = bind(RecvSocket, (SOCKADDR *)&RecvAddr, sizeof(RecvAddr));

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


    //循环接收数据
    while(1)
        {
            //start Timer
            udpTimer->start(60000);

            //Every 60s emit a timeout()
            connect(udpTimer,&QTimer::timeout,this,&MainWindow::TimeUpdate);

            recvdata->UDPRecieve();
        }

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
    qDebug()<<" pushButton_Send_clicked "<<endl;

    //New SendSocket Object
    SendSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    //New Senddata Object
    senddata = new Senddata(SendSocket, ui);

    //ifStream >> sendData
    senddata->ReadFromFiles();

    //sendData >> msgbuf
    senddata->getConfig();

    isStopSend = false;

    while(1)
    {
        //msgbuf >> UDP
        senddata->writeDatagram();

        qDebug()<<"sending data ... "<<endl;

        //delay 1ms
        Sleep(1);
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{
    recvdata->CloseUDP();
}


