#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
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

class Q{
public:
    int n;
    static Semaphore semProd;
    static Semaphore semCon;

    void produce(int value){
        semProd.wait();
        n=value;
        cout<<"Produced: "<<n<<endl;
        semCon.signal();
    }

    void consume(){
        semCon.wait();
        cout<<"Consumed: "<<n<<endl;
        semProd.signal();
    }
};

Semaphore Q::semProd(1);
Semaphore Q::semCon(0);

void producer(Q &q){
    for(int i=1;i<=5;i++){
        q.produce(i);
    }
}

void consumer(Q &q){
    for(int i=1;i<=5;i++){
        q.consume();
    }
}

int main() {
    Q q;
    thread producerThread(producer,ref(q));
    thread consumerThread(consumer,ref(q));

    producerThread.join();
    consumerThread.join();
    
    return 0;
}