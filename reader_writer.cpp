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
class first_type {
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
};
    // csapp 12.19
class first_type_enhaunced {
public:
    // first type reader writer
    // no reader shall be kept waiting if the share is currently opened for reading. This is also called readers-preference
    // 弱读者优先级； 因为读者unlock 后， 可能会唤醒另外一个读者； 那么考虑条件变量！！ 用mutex 和 条件变量就能实现semaphore哦！
    int cnt = 0;
    sem_t mutex, wr; // both initial to 1
                            // wr 用互斥 写 和 所有的读； mutex用于互斥 读之间
    cond_t  cv;
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
            cond_broadcast(&cv);
        }
        unlock(mutex);
    }

    void writer()
    {
        while (1) {

            lock(wr); //lock
            while (!(cnt == 0)) {
                cond_wait(&cv, &wr);
            }
            /*
                critical , do write
            */
            unlock(wr);
        }
    }
};

    // csapp 12.20 at most N readers. equal optunity for writer & reader
class universal {
public:
    const int maxi = 100;
    int cnt = 0;
    sem_t mutex, wr; // both initial to 1
    sem_t read;  initia(&read, maxi)// initai to max
    
    void reader()
    {
        lock(read);

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

        unlock(read);
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
};

// csapp 12.21 second type 
// no writer, once added to the queue, shall be kept waiting longer than absolutely necessary. This is also called writers-preference
class writer_first {    
    int cnt = 0,  wr_cnt = 0;
    sem_t rd_lock, rd_stage1,   // stage1 to block reader
    wr, wr_lock; // both initial to 1

    void reader()
    {
        lock(rd_stage1);  // try to acquire resource
        lock(mutex);
        cnt++;
        if (cnt == 1) {
            lock(wr);
        }
        unlock(mutex);
        unlock(rd_stage1);
        
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
            lock(wr_lock);
            wr_cnt++;
            if (wr_cnt == 1) {
                lock(rd_stage1);
            }
            unlock(wr_lock);  // like reader do to 

            lock(wr); //lock
            /*
                critical , do write
            */
            unlock(wr);

            lock(wr_lock);
            wr_cnt--
            if (wr_cnt == 0) {
                unlock(rd_stage1);
            }
            unlock(wr_lock);  // like reader do to 

        }
    }
};

}
