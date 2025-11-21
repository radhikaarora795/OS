#include <iostream>
#include <thread>
#include <semaphore>
using namespace std;

class Q{
public:
    int n;

    static binary_semaphore semProd;
    static binary_semaphore semCon;

    void produce(int value){
        semProd.acquire();  // wait if producer cannot produce ie semProd is 0
        n=value;    // store produced value in buffer
        cout<<"Produced: "<<n<<endl;
        semCon.release();   // signal consumer that item is ready
    }

    void consume(){
        semCon.acquire();   // wait if buffer is empty ie semCon is 0
        cout<<"Consumed: "<<n<<endl;
        semProd.release();  // signal producer that buffer is empty
    }
};

// initialising semaphores
binary_semaphore Q::semProd(1); // producer starts first
binary_semaphore Q::semCon(0);  // consumer waits initially

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