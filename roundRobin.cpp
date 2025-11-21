#include <iostream>
#include <vector>
#include<queue>
using namespace std;

class Process{
public:
    int id;   // Process ID
    int bt;   // Burst time
    int at;   // Arrival time
    int rem;  // Remaining burst time
    int ct;   // Completion time
    int tat;  // Turnaround time
    int wt;   // Waiting time
    
    Process(int i, int b, int a) : id(i), bt(b), at(a), rem(b), ct(0), tat(0), wt(0)
        {}
};

class RoundRobin{
private:
    vector<Process> processes;
    int tq; // time quantum
public:
    RoundRobin(vector<Process> p, int t) : processes(p), tq(t) 
        {}

    void schedule(){
        queue<int> q;   // stores indices of processes
        int currentTime=0;  // keeps track of how much total time has passed
        int n=processes.size();
        vector<bool> visited(n,false);

        // At the start, add all processes that are available at time = 0 into the queue.
        for(int i=0;i<n;i++){
            if(processes[i].at<=currentTime && !visited[i]){
                q.push(i);
                visited[i]=true;
            }
        }

        while(!q.empty()){
            int pIndex=q.front();
            q.pop();    // Get next process index

            int runTime=min(tq,processes[pIndex].rem);  // Process runs for the smaller of (time quantum, remaining burst time)
            processes[pIndex].rem-=runTime;
            currentTime+=runTime;

            // Add new processes that arrived during this run
            for(int i=0;i<n;i++){
                if(processes[i].at<=currentTime && !visited[i]){
                    q.push(i);
                    visited[i]=true;
                }
            }

            // If process still needs CPU, push it back into queue
            if(processes[pIndex].rem > 0){
                q.push(pIndex);
            }
            else{
                processes[pIndex].ct=currentTime;
                processes[pIndex].tat=processes[pIndex].ct-processes[pIndex].at;
                processes[pIndex].wt=processes[pIndex].tat-processes[pIndex].bt;
            }
        }
    }

    void displayResults(){
        double TAT=0, WT=0;
        cout<<"\nPID\tAT\tBT\tCT\tTAT\tWT\n";
        for(auto p:processes) {
            cout<<"P"<<p.id<<"\t"<<p.at<<"\t"<< p.bt 
                <<"\t"<<p.ct<<"\t"<<p.tat<<"\t"<< p.wt<<"\n";
            TAT+=p.tat;
            WT+=p.wt;
        }
        cout<<"\nAverage Turn Around Time = "<<(TAT/processes.size());
        cout<<"\nAverage Waiting Time =     "<<(WT/processes.size())<<endl;
    }

};

int main() {
    int n,tq;

    cout<<"Enter number of processes: ";
    cin>>n;

    vector<Process> processes;
    for(int i=0;i<n;i++){
        int at,bt;
        cout<<"Enter Arrival Time for Process "<<i+1<<": ";
        cin>>at;
        cout<<"Enter Burst Time for Process   "<<i+1<<": ";
        cin>>bt;

        Process p(i+1,bt,at);
        processes.push_back(p);
    }

    cout<<"Enter Time Quantum: ";
    cin>>tq;

    RoundRobin rr(processes,tq);
    rr.schedule();
    rr.displayResults();

    return 0;
}