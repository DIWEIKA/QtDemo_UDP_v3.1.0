#include "dealmsg.h"

DealMsg::DealMsg(SOCKET socket)
{
    Recvsocket = socket;

    CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);

    //share memory to clientAddr
    ZeroMemory(&clientAddr, sizeof(clientAddr));
}

void DealMsg::setFlag()
{
    isDone = false;
}

void DealMsg::resetFlag()
{
    isDone = true;
}

void DealMsg::run()
{
    while(true){

        if(isDone)
            break;

        RecvBuf[LenoBuf] = {0};

        int clientAddrLen = sizeof(SOCKADDR);

        hasRecv = recvfrom(Recvsocket, RecvBuf, LenoBuf,  0 , (SOCKADDR* )&clientAddr, &clientAddrLen);

        qDebug()<<"hasRecv = "<<hasRecv<<endl;

        if(hasRecv == SOCKET_ERROR)
        {
              qDebug()<<"Error receiving from client"<<WSAGetLastError()<< endl;
              break;
         }

        for(int i=0; i<LenoBuf; i++)
             {
                char usCHDATA =RecvBuf[i];

                //²âÊÔ
                CHdata2->push(usCHDATA);
            }

            qDebug()<<"RecvBuf >> CHdata finished !" << endl;

    }

    qDebug()<<"DealMsg Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;

//    exec();
}
