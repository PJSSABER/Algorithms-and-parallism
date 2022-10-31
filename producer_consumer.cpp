/*
    implementation of Consumer and producer.
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
    channel_cd(int size) {
        assert (size >= 0 && size <= 100); //
        buffer_size = size;
        buffer = new T[buffer_size];
        cur_size = 0;
        COND_INIT();// cv mutex initial
    }

    ~channel_cd() {
        delete[] buffer;
    }

    void* producer(T& tmp) {
        Pthread_mutex_lock(&mutex);
        while (!(cur_size < buffer_size)) {
            Pthread_cond_wait(&cv, &mutex);
        }
        put(tmp);
        Pthread_cond_broadcast(&cv);
        Pthread_mutex_unlock(&mutex);
    }

    void* consumer() {
        Pthread_mutex_lock(&mutex);
        while (!(cur_size > 0)) {
            Pthread_cond_wait(&cv, &mutex);
        }
        get(tmp);
        Pthread_cond_broadcast(&cv);
        Pthread_mutex_unlock(&mutex);
    }

private:
    mutex_t mutex;   // get access to race region
    cond_t  cv;   // conditioan mem
    int buffer_size;
    int cur_size;
    T* buffer; // 存放内容为T的buffer指针 这里当stack使用会更方便

    void put (T& tmp) {
        assert(cur_size >= buffer_size);
        buffer[cur_size] = tmp;
        cur_size++;
    }

    T get () {
        assert(cur_size);
        auto tmp = buffer[cur_size-1];
        cur_size--;
        return  tmp;
    }               // 这里发生了两次拷贝， 后续如何优化？ 
};
// 这个实现的一些问题： 在 多consumer 多 producer的情况下
/*
    condition: 当前producter执行put函数后buffer已经满了， 此时已经还有K个producer因为Pthread_cond_wait函数处于cv条件变量的等待队列中
    此时执行Pthread_cond_signal函数可能唤醒一个producer，导致进行下一次等待； 此情况可能重复出现 导致程序效率下降
    maybe： 看下 notify_one VS notify_all的区别？ 这里使用 notify_all

*/

/* another way using two conditional variable to make sure that 
   when a producer finished, it will only try to awake a consumer.
   and a consumer likewise.
*/
// Using semaphore

// Using spinlock
}


const int mod = 1e9 + 7;
int tr(string& a) {
    
    int len = a.size();

}