/*
    implementation of reader && writer
*/
#include <iostream>
#include <condition_variable>
#ifndef windows
#include<Windows.h>
struct mutex_t {};
#else
#include<pthread.h>
#endif

namespace pjssaber{
// Using condition-variable
template<typename T>
class channel_cd {
public:
    // first type reader writer
    // no reader shall be kept waiting if the share is currently opened for reading. This is also called readers-preference
    int cnt = 0;
    sem_t mutex, wr; // both initial to 1
                            // wr 用互斥 写 和 所有的读； mutex用于互斥 读之间
    void reader()
    {
        lock(mutex);
        cnt++;
        if (cnt == 1) {
            lock(wr);
        }
        unlock(mutex);
        /*
            do read
        */

        lock(mutex);
        cnt--;
        if (cnt == 0) {
            unlock(wr);
        }
        unlock(mutex);
    }

    void writer()
    {
        while (1) {
            lock(wr); //lock
            /*
                critical , do write
            */
            unlock(wr);
        }
    }
    // 弱读者优先级； 因为读者unlock 后， 可能会唤醒另外一个读者

    // csapp 12.19

    // csapp 12.20

    // csapp 12.21 second type 
    // no writer, once added to the queue, shall be kept waiting longer than absolutely necessary. This is also called writers-preference
}
