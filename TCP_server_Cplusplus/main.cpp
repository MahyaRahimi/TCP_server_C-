/* There is no keepcopy function in this version. We don't keep a copy of each listened frame.
 * Data is cin from the user in int format, but is converted to unsigned char when saving analysing. otherwise we
 * cannot enter numbers like 120 and save all the digits (only first digit will be saved
 * In this version whoole mesage processing and demand answering is in one thread. */


#include "listener.h"
#include "tcp.h"
#include "transmitter.h"


#include <thread>
#include <iostream>
#include <set>
/*#include <string.h>
#include <tuple>
#include <mutex>
#include <condition_variable>*/

std::mutex m_lis_tcp;                                            //for exclusive access to memory_between tcp and listener
std::condition_variable cv_lis_tcp;                              //blocks the calling thread until notified to resume
int listening_sign;                                              //a sign for notifying tcp that listener has restarted
std::mutex m;                                                    //for exclusive access to memory
std::condition_variable cv;                                      //blocks the calling thread until notified to resume
std::vector<unsigned char> myvector = {};                        //each element of myvector is a byte of data
int count1;


int main()
{

    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    /* create listener thread: */
    listener objlistener;
    std::thread threadlistener(&listener::listening, objlistener);//creates thread threadlistener that calls listener()
    /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/


    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    /* create transmitter thread : */
    transmitter objtransmit;
    std::thread threadtransmit(&transmitter::transmit, objtransmit);//creates thread threadtransmit that calls transmit()
    /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    /* create tcp thread : */
    TCP objTCP;
    std::thread threadTCP(&TCP::connecting, objTCP);//creates thread threadTCP that calls connecting()
    /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/


    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    /* thread join */
    threadlistener.join();//pauses until threadlistener finishes
    threadtransmit.join();
    threadTCP.join();
    /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

    return 0;
}
