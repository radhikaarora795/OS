#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>
#include <unistd.h> // for sleep()
using namespace std;

sem_t resource; // controls access to the shared resource
sem_t rmutex;   // ensures that only one thread can modify readCount at a time
int readCount = 0; // number of readers currently reading
int sharedData = 0; // shared resource

void reader(int id) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&rmutex);       // lock rmutex before changing readCount
        readCount++;
        if (readCount == 1) {    // first reader locks the resource
            sem_wait(&resource);
        }
        sem_post(&rmutex);       // unlock rmutex

        // reading section
        cout << "Reader " << id << " reads: " << sharedData << endl;
        sleep(1);

        sem_wait(&rmutex);       // lock again to decrement readCount
        readCount--;
        if (readCount == 0) {    // last reader unlocks the resource
            sem_post(&resource);
        }
        sem_post(&rmutex);       // unlock rmutex
        sleep(1);
    }
}

void writer(int id) {
    for (int i = 0; i < 5; i++) {
        sem_wait(&resource);      // lock resource for exclusive access
        sharedData++;
        cout << "Writer " << id << " writes: " << sharedData << endl;
        sleep(2);                 // simulate writing
        sem_post(&resource);      // unlock resource
        sleep(1);
    }
}

int main() {
    // initialize semaphores
    sem_init(&resource, 0, 1);
    sem_init(&rmutex, 0, 1);

    vector<thread> readers, writers;

    // create 5 readers
    for (int i = 1; i <= 5; i++) {
        readers.push_back(thread(reader, i));
    }

    // create 3 writers
    for (int i = 1; i <= 3; i++) {
        writers.push_back(thread(writer, i));
    }

    // join all threads
    for (auto &r : readers) r.join();
    for (auto &w : writers) w.join();

    // destroy semaphores
    sem_destroy(&resource);
    sem_destroy(&rmutex);

    return 0;
}
