/*
#include <iostream>
#include <algorithm>
using namespace std;

class Process{
public:
    int id;
    int bt;
    int wt;
    int tat;

    Process():id(0),bt(0),wt(0),tat(0)
        {}
};

class FCFS{
private:
    Process *p;
    int n;
public:
    FCFS(Process *arr,int size):n(size){
        p=new Process[n];
        for(int i=0;i<n;i++){
            p[i]=arr[i];
        }
    }

    void calculate(){
        p[0].wt=0;
        for(int i=1;i<n;i++){
            p[i].wt=p[i-1].wt+p[i-1].bt;
        }
        for(int i=0;i<n;i++){
            p[i].tat=p[i].bt+p[i].wt;
        }
    }

    void display(){
        int totalWT=0;
        int totalTAT=0;
        cout<<"Process"
            <<"\tBT"
            <<"\tWT"
            <<"\tTAT"<<endl;
        
        for(int i=0;i<n;i++){
            cout<<"P"<<p[i].id<<"\t"
                <<p[i].bt<<"\t"
                <<p[i].wt<<"\t"
                <<p[i].tat<<endl;

            totalWT+=p[i].wt;
            totalTAT+=p[i].tat;
        }

        cout<<"Average waiting time = "<<(float)totalWT/n<<endl;
        cout<<"Average turn around time = "<<(float)totalTAT/n<<endl;
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    Process *p=new Process[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        cout<<"BT for Process "<<p[i].id<<": ";
        cin>>p[i].bt;
    }

    FCFS f(p,n);
    f.calculate();
    f.display();

    return 0;
}
*/

/*
#include <iostream>
#include <algorithm>
using namespace std;

class Process{
public:
    int id;
    int bt;
    int wt;
    int tat;

    Process():id(0),bt(0),wt(0),tat(0)
        {}
};

class SJF{
private:
    Process *p;
    int n;
public:
    SJF(Process *arr,int size):n(size){
        p=new Process[n];
        for(int i=0;i<n;i++){
            p[i]=arr[i];
        }
    }

    void sortByBurstTime(){
        sort(p,p+n,[](Process a,Process b){
            return a.bt<b.bt;
        });
    }

    void calculate(){
        p[0].wt=0;

        for(int i=1;i<n;i++){
            p[i].wt=p[i-1].wt+p[i-1].bt;
        }

        for(int i=0;i<n;i++){
            p[i].tat=p[i].bt+p[i].wt;
        }
    }

    void display(){
        int totalWT=0;
        int totalTAT=0;

        cout<<"Process"
            <<"\tBT"
            <<"\tWT"
            <<"\tTAT"<<endl;

        for(int i=0;i<n;i++){
            cout<<"P"<<p[i].id<<"\t"
                <<p[i].bt<<"\t"
                <<p[i].wt<<"\t"
                <<p[i].tat<<endl;

            totalWT+=p[i].wt;
            totalTAT+=p[i].tat;
        }
        cout<<"Average waiting time = "<<(float)totalWT/n<<endl;
        cout<<"Average turn around time = "<<(float)totalTAT/n<<endl;
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    Process *p=new Process[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        cout<<"BT for Process "<<p[i].id<<": ";
        cin>>p[i].bt;
    }

    SJF s(p,n);
    s.sortByBurstTime();
    s.calculate();
    s.display();
    
    return 0;
}
*/

/*
#include <iostream>
using namespace std;

class Process{
public:
    int id,at,bt,rt,ct,tat,wt;
    bool completed;

    Process():id(0),at(0),bt(0),rt(0),ct(0),tat(0),wt(0),completed(false)
        {}

    Process(int i,int a,int b):id(i),at(a),bt(b),rt(b),ct(0),tat(0),wt(0),completed(false)
        {}
};

class SRJF{
private:
    Process *p;
    int n;
public:
    SRJF(int size):n(size){
        p=new Process[n];
    }

    void addProcess(int i,int at,int bt){
        p[i]=Process(i+1,at,bt);
    }

    void schedule(){
        int time=0;
        int completed=0;
        float avgTAT=0;
        float avgWT=0;

        while(completed != n){
            int index=-1;
            int minRemainingTime=-1;

            for(int i=0;i<n;i++){
                if(p[i].at<=time && !p[i].completed){
                    if(minRemainingTime==-1 || p[i].rt<minRemainingTime){
                        minRemainingTime=p[i].rt;
                        index=i;
                    }
                }
            }
            if(index != -1){
                p[index].rt--;
                time++;

                if(p[index].rt==0){
                    p[index].completed=true;
                    p[index].ct=time;
                    p[index].tat=p[index].ct-p[index].at;
                    p[index].wt=p[index].tat-p[index].bt;
                    avgTAT+=p[index].tat;
                    avgWT+=p[index].wt;
                    completed++;
                }
            }
            else{
                time++;
            }
        }
        display(avgTAT,avgWT);
    }

    void display(float avgTAT, float avgWT){
        cout<<"ID\tAT\tBT\tCT\tTAT\tWT"<<endl;
        for(int i=0;i<n;i++){
            cout<<p[i].id<<"\t"
            <<p[i].at<<"\t"
            <<p[i].bt<<"\t"
            <<p[i].ct<<"\t"
            <<p[i].tat<<"\t"
            <<p[i].wt<<endl;
        }

        cout<<"Average TAT: "<<(avgTAT/n)<<endl;
        cout<<"Average WT: "<<(avgWT/n)<<endl;
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    SRJF s(n);
    for(int i=0;i<n;i++){
        int at,bt;
        cout<<"Enter AT for process "<<i+1<<": ";
        cin>>at;
        cout<<"Enter BT for process "<<i+1<<": ";
        cin>>bt;
        s.addProcess(i,at,bt);
    }

    s. 
    
    return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Process{
public:
    int id,bt,at,rt,ct,tat,wt;

    Process(int i,int b,int a):id(i),bt(b),at(a),rt(b),ct(0),tat(0),wt(0)
        {}
};

class RoundRobin{
private:
    vector<Process> p;
    int tq;
public:
    RoundRobin(vector<Process> arr,int t):p(arr),tq(t)
        {}
    
    void schedule(){
        queue<int> q;
        int currentTime=0;
        int n=p.size();
        vector<bool> visited(n,false);

        for(int i=0;i<n;i++){
            if(p[i].at<=currentTime && !visited[i]){
                q.push(i);
                visited[i]=true;
            }
        }

        while(!q.empty()){
            int pIndex=q.front();
            q.pop();

            int runTime=min(tq,p[pIndex].rt);
            p[pIndex].rt-=runTime;
            currentTime+=runTime;

            for(int i=0;i<n;i++){
                if(p[i].at<=currentTime && !visited[i]){
                    q.push(i);
                    visited[i]=true;
                }
            }
            if(p[pIndex].rt>0){
                q.push(pIndex);
            }
            else{
                p[pIndex].ct=currentTime;
                p[pIndex].tat=p[pIndex].ct-p[pIndex].at;
                p[pIndex].wt=p[pIndex].tat-p[pIndex].bt;
            }
        }
    }

    void display(){
        double TAT=0,WT=0;
        cout<<"id\tAT\tBT\tCT\tTAT\tWT"<<endl;
        for(auto pr:p){
            cout<<"P"<<pr.id<<"\t"
                <<pr.at<<"\t"
                <<pr.bt<<"\t"
                <<pr.ct<<"\t"
                <<pr.tat<<"\t"
                <<pr.wt<<endl;
        
            TAT+=pr.tat;
            WT+=pr.wt;
        }
        cout<<"Average Turn Around Time = "<<(TAT/p.size())<<endl;
        cout<<"Average Waiting Time     = "<<(WT/p.size())<<endl;
    }
};

int main() {
    int n,tq;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<Process> processes;
    for(int i=0;i<n;i++){
        int at,bt;
        cout<<"Enter AT for process "<<i+1<<": ";
        cin>>at;
        cout<<"Enter BT for process "<<i+1<<": ";
        cin>>bt;

        Process p(i+1,bt,at);
        processes.push_back(p);
    }

    cout<<"Enter time quantum: ";
    cin>>tq;

    RoundRobin r(processes,tq);
    r.schedule();
    r.display();
    
    return 0;
}
*/

/*
#include <iostream>
#include <vector>
using namespace std;

class Process{
public:
    int id,bt,at,priority,ct,tat,wt;
    bool completed;

    Process(int i,int b,int a,int p):id(i),bt(b),at(a),priority(p),ct(0),tat(0),wt(0),completed(false)
        {}
};

class Priority{
private:
    vector<Process> p;
public:
    Priority(vector<Process> arr):p(arr)
        {}

    void schedule(){
        int n=p.size();
        int completedCount=0;
        int currentTime=0;

        while(completedCount<n){
            int index=-1;
            int highestPriority=-1;

            for(int i=0;i<n;i++){
                if(!p[i].completed && p[i].at<=currentTime){
                    if(p[i].priority>highestPriority){
                        highestPriority=p[i].priority;
                        index=i;
                    }
                    else if(p[i].priority==highestPriority){
                        if(p[i].at<p[index].at){
                            index=i;
                        }
                    }
                }
            }
            if(index == -1){
                currentTime++;
            }
            else{
                p[index].ct=currentTime+p[index].bt;
                p[index].tat=p[index].ct-p[index].at;
                p[index].wt=p[index].tat-p[index].bt;
                p[index].completed=true;

                currentTime=p[index].ct;
                completedCount++;
            }
        }
    }
    void display(){
        double TAT=0,WT=0;
        cout<<"id\tAT\tBT\tPriority\tCT\tTAT\tWT"<<endl;
        for(auto pr:p){
            cout<<"P"<<pr.id<<"\t"
                <<pr.at<<"\t"
                <<pr.bt<<"\t"
                <<pr.priority<<"\t\t"
                <<pr.ct<<"\t"
                <<pr.tat<<"\t"
                <<pr.wt<<endl;
        
            TAT+=pr.tat;
            WT+=pr.wt;
        }
        cout<<"Average Turn Around Time = "<<(TAT/p.size())<<endl;
        cout<<"Average Waiting Time     = "<<(WT/p.size())<<endl;
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<Process> processes;
    for(int i=0;i<n;i++){
        int at,bt,priority;
        cout<<"Enter AT for process "<<i+1<<": ";
        cin>>at;
        cout<<"Enter BT for process "<<i+1<<": ";
        cin>>bt;
        cout<<"Enter priority for process "<<i+1<<": ";
        cin>>priority;

        Process p(i+1,bt,at,priority);
        processes.push_back(p);
    }

    Priority p(processes);
    p.schedule();
    p.display();
    return 0;
}
*/

/*
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
*/

/*
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
*/

/*
#include <iostream>
#include <vector>
using namespace std;

void display(vector<int> allocation){
    for(int i=0;i<allocation.size();i++){
        if(allocation[i] != -1){
            cout<<"Process "<<i+1<<" allocated to Block "<<allocation[i]+1<<endl;
        }
        else{
            cout<<"Process "<<i+1<<" not allocated"<<endl;
        }
    }
}

void firstFit(vector<int> blockSize,vector<int> processSize){
    int n=processSize.size();
    int m=blockSize.size();
    vector<int> allocation(n,-1);

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(blockSize[j]>=processSize[i]){
                allocation[i]=j;
                blockSize[j]-=processSize[i];
                break;
            }
        }
    }
    cout<<"First Fit"<<endl;
    display(allocation);
}

void bestFit(vector<int> blockSize,vector<int> processSize){
    int n=processSize.size();
    int m=blockSize.size();
    vector<int> allocation(n,-1);

    for(int i=0;i<n;i++){
        int bestIndex=-1;
        for(int j=0;j<m;j++){
            if(blockSize[j]>=processSize[i]){
                if(bestIndex == -1 || blockSize[j]<blockSize[bestIndex]){
                    bestIndex=j;
                }
            }
        }
        if(bestIndex != -1){
            allocation[i]=bestIndex;
            blockSize[bestIndex]-=processSize[i];
        }
    }
    cout<<"Best Fit"<<endl;
    display(allocation);
}

void worstFit(vector<int> blockSize,vector<int> processSize){
    int n=processSize.size();
    int m=blockSize.size();
    vector<int> allocation(n,-1);

    for(int i=0;i<n;i++){
        int worstIndex=-1;
        for(int j=0;j<m;j++){
            if(blockSize[j]>=processSize[i]){
                if(worstIndex == -1 || blockSize[j]>blockSize[worstIndex]){
                    worstIndex=j;
                }
            }
        }
        if(worstIndex != -1){
            allocation[i]=worstIndex;
            blockSize[worstIndex]-=processSize[i];
        }
    }
    cout<<"Worst Fit"<<endl;
    display(allocation);
}

int main() {
    int m,n;
    cout<<"Enter number of memory blocks: ";
    cin>>m;
    vector<int> blockSize(m);
    for(int i=0;i<m;i++){
        cout<<"Enter memory size of block "<<i+1<<": ";
        cin>>blockSize[i];
    }

    cout<<"Enter number of processes: ";
    cin>>n;
    vector<int> processSize(n);
    for(int i=0;i<n;i++){
        cout<<"Enter memory size of process "<<i+1<<": ";
        cin>>processSize[i];
    }

    firstFit(blockSize,processSize);
    bestFit(blockSize,processSize);
    worstFit(blockSize,processSize);
    
    return 0;
}
*/

/*
#include <iostream>
#include <vector>
using namespace std;

void bankersAlgorithm(int n,int m,vector<vector<int>>& allocation,vector<vector<int>> max,vector<int> available){
    vector<vector<int>> need(n,vector<int>(m));
    cout<<"Need Matrix: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-allocation[i][j];
            cout<<need[i][j]<<" ";
        }
        cout<<endl;
    }

    vector<int> finish(n,0);
    vector<int> safeSequence;

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            if(finish[i]==0){
                bool possible=true;
                for(int j=0;j<m;j++){
                    if(need[i][j]>available[j]){
                        possible=false;
                        break;
                    }
                }
                if(possible){
                    for(int j=0;j<m;j++){
                        available[j]+=allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i]=1;
                }
            }
        }
    }
    bool safe=true;
    for(int i=0;i<n;i++){
        if(finish[i]==0){
            safe=false;
        }
    }
    if(safe){
        cout<<"System is in Safe State"<<endl;
        cout<<"Safe Sequence: ";
        for(int p:safeSequence){
            cout<<"P"<<p<<" ";
        }
    }
    else{
        cout<<"System is not in safe state"<<endl;
    }
}

int main() {
    int n,m;
    cout<<"Enter number of processes: ";
    cin>>n;
    cout<<"Enter number of resource types: ";
    cin>>m;

    vector<vector<int>> allocation(n,vector<int>(m));
    vector<vector<int>> max(n,vector<int>(m));
    vector<int> available(m);

    cout<<"Enter Allocation Matrix: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>allocation[i][j];
        }
    }
    cout<<"Enter Max Matrix: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>max[i][j];
        }
    }
    cout<<"Enter Available Matrix: "<<endl;
    for(int i=0;i<m;i++){
        cin>>available[i];
    }

    bankersAlgorithm(n,m,allocation,max,available);
    
    return 0;
}
*/