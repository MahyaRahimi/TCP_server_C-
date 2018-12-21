#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "tcp.h"

extern std::mutex m;                             //for exclusive access to memory; between listener and transmitter
extern std::condition_variable cv;               //blocks the calling thread until notified to resume
extern int count1;

extern std::vector<unsigned char> myvector;      //each element of myvector is a byte of data

class transmitter: public TCP
{
public:
    transmitter(){}
    void transmit();
    int writing(int socket, char Buff[], int size);
private:
    std::vector <unsigned char> data_to_transmit;
   // std::vector <int> int_data_to_transmit;

};

#endif // TRANSMITTER_H
