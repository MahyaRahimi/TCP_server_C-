#include "tcp.h"

TCP::TCP()
{

}
int TCP::connecting()
{
    /* mutex between TCP and listener*/
    /* locks to connect: */
    {
        std::unique_lock<std::mutex> lk(m_lis_tcp);

        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("socket retrieve success\n");

        memset(&serv_addr, '0', sizeof(serv_addr));
        memset(sendBuff, 0, sizeof(sendBuff));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(4000);

        if(bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
            std::cout << "Error in TCP socket bind!"<< std::endl;

        if(listen(listenfd, 10) == -1){
            printf("Failed to listen\n");
            return -1;
        }
        connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
        /*strcpy(sendBuff, "Message from server\n");
        //std::copy(&buffer[0], &buffer[100], back_inserter(myvector));

        writing(connfd, sendBuff, strlen(sendBuff));*/
        /*--------------------------debug-----------------------------------------------------------------------------------------------------------------------------------------------------*/
       /* memset(buffer, 0, sizeof(buffer));
        std::cout<<"1. do print:\nbuffer is:";
        for (int i=0; i<100; i++)
            std::cout << int(buffer[i]) << " ";
        std::cout << "\nmyvector before filling is: ";
        int k=0;
        for (auto v : myvector)
        {
                std::cout << k << ":" << std::hex << int(v) << " ";
                k++;
        }
        std::cout<<std::endl;*/
        /*--------------------------debug-----------------------------------------------------------------------------------------------------------------------------------------------------*/
        listening_sign = 1;         //if listening_sign is equal to 1, after notification listener will be unlocked.

    }
    /* notify listener thread to finish waiting and start: */
    cv_lis_tcp.notify_all();

    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    /*wait till listener thread change listening_sign to 0: */
    {
        std::unique_lock<std::mutex> lk(m_lis_tcp);
        while(listening_sign) cv_lis_tcp.wait(lk);
    }
    /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
    /*--------------------------debug-----------------------------------------------------------------------------------------------------------------------------------------------------*/
    std::cout<<"back to the TCP" <<std::endl;
    /*--------------------------debug-----------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*--------------------------debug-----------------------------------------------------------------------------------------------------------------------------------------------------*/
    /* send messages to the client via TCP: */
    memset(sendBuff, 0, sizeof(sendBuff));
    strcpy(sendBuff, "\nMessage from server in TCP\n");
    write(connfd, sendBuff, strlen(sendBuff));
    /*--------------------------debug-----------------------------------------------------------------------------------------------------------------------------------------------------*/

    return 0;
}
int TCP::writing(int socket, char  Buff[], int size)
{
    int n = write(socket, Buff, size);
    return n;
}
