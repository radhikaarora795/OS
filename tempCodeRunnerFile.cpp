// non preemptive
#include <iostream>
#include <vector>
using namespace std;

class Process {
public:
    int id;    // Process ID
    int bt;    // Burst time
    int at;    // Arrival time
    int priority;    // Priority (higher number = higher priority)
    int ct;    // Completion time
    int tat;   // Turnaround time
    int wt;    // Waiting time
    bool completed;

    Process(int i, int b, int a, int p) : id(i), bt(b), at(a), priority(p), ct(0), tat(0), wt(0), completed(false)
        {}
};

class Priority{
private:
    vector<Process> processes;
public:
    Priority(vector<Process> p):processes(p)
        {}

    void schedule(){
        int n=processes.size();
        int completedCount=0;   // no. of finished processes
        int currentTime=0;    // keeps track of how much total time has passed

        while(completedCount<n){
            int pIndex=-1;  // index of chosen process
            int highestPriority=-1;

            for(int i=0;i<n;i++){
                // Check if this process has already arrived and it has not yet been completed.
                if(!processes[i].completed && processes[i].at<=currentTime){
                    // Check if the i-th process has a higher priority than the one selected so far
                    if(processes[i].priority>highestPriority){
                        highestPriority=processes[i].priority;
                        pIndex=i;
                    }
                    // // If same priority, choose earlier arrival
                    else if(processes[i].priority == highestPriority){
                        if(processes[i].at<processes[pIndex].at){
                            pIndex=i;
                        }
                    }
                }
            }
            
            // No process ready, CPU idle
            if(pIndex==-1){
                currentTime++;
            }
            else{
                processes[pIndex].ct = currentTime + processes[pIndex].bt;
                processes[pIndex].tat = processes[pIndex].ct - processes[pIndex].at;
                processes[pIndex].wt = processes[pIndex].tat - processes[pIndex].bt;
                processes[pIndex].completed = true;

                currentTime = processes[pIndex].ct;
                completedCount++;
            }
        }
    }

     void displayResults() {
        double totalTAT=0,totalWT=0;

        cout<<"\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
        for(auto p:processes) {
            cout<<"P"<<p.id<<"\t"<<p.at<<"\t"<<p.bt
                <<"\t"<<p.priority<<"\t\t"<<p.ct
                <<"\t"<<p.tat<<"\t"<<p.wt<<"\n";
            totalTAT+=p.tat;
            totalWT+=p.wt;
        }

        cout<<"\nAverage Turnaround Time = "<<(totalTAT/processes.size());
        cout<<"\nAverage Waiting Time    = "<<(totalWT/processes.size())<<endl;
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<Process> processes;
    for(int i=0;i<n;i++){
        int at,bt,priority;
        cout<<"Enter Arrival Time for Process "<<i+1<<": ";
        cin>>at;
        cout<<"Enter Burst Time for Process   "<<i+1<<": ";
        cin>>bt;
        cout<<"Enter Priority for Process     "<<i+1<<": ";
        cin>>priority;

        Process p(i+1,bt,at,priority);
        processes.push_back(p);
    }

    Priority p(processes);
    p.schedule();
    p.displayResults();
    
    return 0;
}