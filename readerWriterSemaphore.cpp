#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <unistd.h> // for sleep()
using namespace std;

sem_t resource; // controls access to the shared resource
sem_t rmutex;  // ensures that only one thread at a time can access or modify the variable readcount
int readCount=0; // number of readers reading
int sharedData=0; // shared data

void reader(int id){
    for(int i=0;i<3;i++){
        sem_wait(&rmutex);  // lock rmutex so that no other reader can simulatneously modify readCount
        readCount++;
        if(readCount==1){   // first reader locks resource to prevent writers from writing when readers are reading
            sem_wait(&resource);
        }
        sem_post(&rmutex);  // unlock rmutex
        //<<"Reader "<<id<<" reads: "<<sharedData<<endl;
        cout<<"Reader "<<id<<" reads: "<<sharedData<<endl;
        sleep(1);
        sem_wait(&rmutex);  // lock rmutex again to decrement readCount when reader finishes reading
        readCount--;
        if(readCount==0){   // if last reader, release resource so writers can can access the resource
            sem_post(&resource);
        }
        sem_post(&rmutex);  // unlock rmutex
        sleep(1);
    }
}

void writer(int id){
    for(int i=0;i<3;i++){
        sem_wait(&resource);    // lock resource to write, no other reader or writer can access it now
        sharedData++;
        //cout<<"Writer "<<id<<" writes: "<<sharedData<<endl;
        cout<<"Writer "<<id<<" writes: "<<sharedData<<endl;
        sleep(2);
        sem_post(&resource);    // unlock resource
        sleep(1);
    }
}

int main() {
    sem_init(&resource, 0, 1);
    sem_init(&rmutex, 0, 1);

    vector<thread> readers,writers;

    for(int i=1;i<=3;i++){  // 3 readers
        readers.push_back(thread(reader,i));
        usleep(100000);
    }
    for(int i=1;i<=2;i++){  // 2 writers
        writers.push_back(thread(writer,i));
        usleep(100000);
    }

    for(auto &r:readers){
        r.join();
    }
    for(auto &w:writers){
        w.join();
    }
    
    sem_destroy(&resource);
    sem_destroy(&rmutex);

    return 0;
}