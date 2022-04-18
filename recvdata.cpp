#include "recvdata.h"

Recvdata::Recvdata(SOCKET socket, Ui::MainWindow *ui)
{
    Recvsocket = socket;

    UI = ui;

//    //init RecvBuf
//    RecvBuf[LenoBuf];

    //share memory to clientAddr
    ZeroMemory(&clientAddr, sizeof(clientAddr));

    //CHdata初始化 。
    CHdata2 = make_shared<CirQueue<char>>(LenoUDP);
}

Recvdata::~Recvdata()
{

}

void Recvdata:: UDPRecieve()
{
       //RecvBuf << UDP
       readDatagram();

       if(hasRecv == SOCKET_ERROR)
       {
             qDebug()<<"Error receiving from client"<<WSAGetLastError()<< endl;
             return;
        }

       //CHData << RecvBuf
       getDatafromBufToCHdata();

       //close UDP socket
       CloseUDP();
}

void Recvdata::readDatagram()
{

    int clientAddrLen = sizeof(SOCKADDR);

    //读取对方发送的内容，并存入RecvBuf
    hasRecv = recvfrom(Recvsocket, RecvBuf, LenoBuf,  0 , (SOCKADDR* )&clientAddr, &clientAddrLen);

    qDebug()<<"hasRecv = "<<hasRecv<<endl;
}

void Recvdata:: changeFileNameOnce()
{
    //更新当前时间
    dateTime = QDateTime::currentDateTime();

    saveFolder =  string("F:/Desktop/UDPConnect/data/");

    saveFilename1 = QString(saveFolder.c_str())+QString("/[CH1][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilename2 = QString(saveFolder.c_str())+QString("/[CH2][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilename3 = QString(saveFolder.c_str())+QString("/[CH3][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

}

void Recvdata::getDatafromBufToCHdata()
{

    for(int i=0; i<LenoBuf; i++)
     {
        char usCHDATA =RecvBuf[i];

//        qDebug()<< "usCHDATA = "<< usCHDATA<<endl;

        //测试
        CHdata2->push(usCHDATA);
    }
}

void Recvdata:: WriteToFilesWith3Channels()
{
    //打开文件
   outfile1.open(saveFilename1.toStdString().data(),ofstream::binary);
   outfile2.open(saveFilename2.toStdString().data(),ofstream::binary);
   outfile3.open(saveFilename3.toStdString().data(), ofstream::binary);

    //打开文件失败则结束运行
    if (!outfile1.is_open() || !outfile2.is_open() || !outfile3.is_open()) return;

    unsigned int lenoCHdata = CHdata2->size();

    //按先后顺序将CH1、CH2、CH3的数据分开存储
    for(unsigned int i=0; i<lenoCHdata/3; ++i)
    {
        outfile1.write((const char*)CHdata2->begin(),sizeof (char));
        CHdata2->pop();
        outfile2.write((const char*)CHdata2->begin(),sizeof (char));
        CHdata2->pop();
        outfile3.write((const char*)CHdata2->begin(),sizeof (char));
        CHdata2->pop();
    }

    //clear CHdata
    CHdata2->clear();

    qDebug()<<"ofstream writing over ! "<<endl;

    qDebug()<<"CHdata have been cleared ! "<<endl;

}

void Recvdata::closeStream()
{
    //关闭输出流
    outfile1.close();
    outfile2.close();
    outfile3.close();
}

void Recvdata::CloseUDP()
{
         //close Recvsocket
        qDebug()<<"finished receiving, closing socket"<<endl;

        closesocket(Recvsocket);

        //Shutdown Winsock
        qDebug()<<"Exiting..."<<endl;

        WSACleanup();
}

