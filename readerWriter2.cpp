#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
using namespace std;

class Semaphore{
    mutex m;
    condition_variable cv;
    int count;
public:
    Semaphore(int c=0):count(c)
        {}

    void wait(){
        unique_lock<mutex> lock(m);
        cv.wait(lock,[&]{return count>0;});
        count--;
    }

    void signal(){
        unique_lock<mutex> lock(m);
        count++;
        cv.notify_one();
    }
};

Semaphore mutex_readCount(1);
Semaphore rw_mutex(1);

int readCount=0;
int sharedData=0;

void reader(int id){
    mutex_readCount.wait();
    readCount++;
    if(readCount == 1){
        rw_mutex.wait();
    }
    mutex_readCount.signal();
    cout<<("Reader "+to_string(id)+" reads = "+to_string(sharedData)+"\n");
    mutex_readCount.wait();
    readCount--;
    if(readCount == 0){
        rw_mutex.signal();
    }
    mutex_readCount.signal();
}

void writer(int id){
    rw_mutex.wait();
    sharedData++;
    cout<<("Writer "+to_string(id)+" writes = "+to_string(sharedData)+"\n");
    rw_mutex.signal();
}   

int main() {
    vector<thread> t;

    for(int i=0;i<=3;i++){
        t.push_back(thread(reader,i));
    }
    for(int i=1;i<=2;i++){
        t.push_back(thread(writer,i));
    }

    for(auto &th:t){
        th.join();
    }
    
    return 0;
}