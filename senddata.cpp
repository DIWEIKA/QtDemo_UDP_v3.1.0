#include "senddata.h"

Senddata::Senddata(SOCKET socket, Ui::MainWindow *ui)
{
    Sendsocket = socket;

    UI = ui;
}

Senddata:: ~Senddata()
{

}

void Senddata:: ReadFromFiles()
{
    //file dir
    saveFolder  = QString("F:/Desktop/UDPConnect/");
    file = saveFolder + QString("SendData2")+QString(".txt");

    //open file
    infile.open(file.toStdString().data(),ios_base::in);

    //
    sendData.resize(200000);

    //if open failed, exit
    if(!infile.is_open())
    {
        qDebug()<< "open file failed !" << endl;
    }

    //ifstream >> sendData
    while(getline(infile, sendData))
    {
        qDebug()<< "reading file succeed !" << endl;
    }

    //close ifstream
    infile.close();
}

void Senddata::getConfig()
{
    //´ý·¢ËÍÏûÏ¢buf
    msgbuf = QByteArray::fromStdString(sendData);
  //  msgbuf = QString(sendData.c_str());

    //Destination IP
    DestIP = UI->lineEdit_Ip->text();

    //Destination port
    DestPort = UI->lineEdit_Port->text().toInt();

    //set RecvAddr
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(DestPort);
    RecvAddr.sin_addr.S_un.S_addr = inet_addr(DestIP.toLatin1());

}

void Senddata:: writeDatagram()
{
    Lenobuf = msgbuf.length();

    //msgbuf >>UDP
    int sendOk = sendto(Sendsocket,msgbuf,Lenobuf,0,(SOCKADDR*)&RecvAddr, sizeof(RecvAddr));

    if(sendOk == SOCKET_ERROR)
    {
        qDebug()<<"Send didn't work! "<<WSAGetLastError()<<endl;
    }
}

void Senddata::closeUDP()
{
    //close Sendsocket
   qDebug()<<"finished sending, closing socket"<<endl;
    closesocket(Sendsocket);

    WSACleanup();
}
