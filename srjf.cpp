#include <iostream>
using namespace std;

class Process{
public:
    int id, at, bt, rt, ct, tat, wt;
    bool completed;

    Process(): id(0), at(0), bt(0), rt(0), ct(0), tat(0), wt(0), completed(false) 
        {}


    Process(int i, int a, int b): id(i), at(a), bt(b), rt(b), ct(0), tat(0), wt(0), completed(false) 
        {}
};

//Shortest Remaining Job First
class SRJF{
    Process* processes;
    int n;
public:
    SRJF(int size):n(size){
        processes=new Process[n]; // allocate array of processes
    }

    void addProcess(int i, int at, int bt){
        processes[i]=Process(i+1, at, bt); 
    }

    void schedule(){
        int time=0, completedCount=0;
        float avgTAT=0, avgWT=0;

        while(completedCount!=n){
            int idx=-1;
            int mn=-1;

            for(int i=0;i<n;i++){
                if(processes[i].at<=time && !processes[i].completed){
                    if(mn==-1 || processes[i].rt<mn) {
                        mn=processes[i].rt;
                        idx=i;
                    }
                }
            }

            if(idx!=-1){
                processes[idx].rt--;
                time++;

                if(processes[idx].rt==0){
                    processes[idx].completed=true;
                    processes[idx].ct=time;
                    processes[idx].tat=processes[idx].ct-processes[idx].at;
                    processes[idx].wt=processes[idx].tat-processes[idx].bt;
                    avgTAT+=processes[idx].tat;
                    avgWT+=processes[idx].wt;
                    completedCount++;
                }
            } else {
                time++; // CPU idle
            }
        }

        display(avgTAT, avgWT);
    }

    void display(float avgTAT, float avgWT) {
        cout << "\nID\tAT\tBT\tCT\tTAT\tWT\n";
        for (int i = 0; i < n; i++) {
            cout<<processes[i].id<<"\t"
                <<processes[i].at<<"\t"
                <<processes[i].bt<<"\t"
                <<processes[i].ct<<"\t"
                <<processes[i].tat<<"\t"
                <<processes[i].wt<<"\n";
        }
        cout<<endl<<"Average TAT : "<<(avgTAT/n)<<endl;
        cout<<"Average WT  : "<<(avgWT/n)<<endl;
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    SRJF s(n);
    for(int i=0;i<n;i++){
        int at, bt;
        cout<<"Enter AT for Process "<<i+1<<": ";
        cin>>at;
        cout<<"Enter BT for Process "<<i+1<<": ";
        cin>>bt;
        s.addProcess(i, at, bt);
    }

    cout<<endl<<"Shortest Remaining Job First (SRJF): "<<endl;
    s.schedule();
    return 0;
}
