#include <iostream>
using namespace std;

class Process {
public:
    int id;              // process ID
    int burstTime;       // CPU burst time
    int waitingTime;     
    int turnAroundTime;

    Process():id(0),burstTime(0),waitingTime(0),turnAroundTime(0)
        {}
};

//Shortest Job First 
class SJF {
private:
    Process *p;   //Array of objects
    int n;        //Number of processes
public:
    SJF(Process *arr,int size): n(size){
        p=new Process[n];
        for(int i=0;i<n;i++){
            p[i]=arr[i];
        }
    }

    //Sort processes based on Burst Time
    void sortByBurstTime(){
        sort(p,p+n,[](Process a, Process b){
            return a.burstTime<b.burstTime;
        });
    }

    void calculate() {
        p[0].waitingTime = 0; // First process has 0 waiting time

        for(int i=1;i<n;i++){
            p[i].waitingTime=p[i - 1].waitingTime+p[i - 1].burstTime;
        }

        for(int i=0;i<n;i++) {
            p[i].turnAroundTime=p[i].burstTime+p[i].waitingTime;
        }
    }

    void display() {
        int totalWT=0;
        int totalTAT=0;

        cout<<"\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
        for(int i=0;i<n;i++) {
            cout<<"P"<<p[i].id<<"\t"
                <<p[i].burstTime<<"\t\t"
                <<p[i].waitingTime<<"\t\t"
                <<p[i].turnAroundTime<<"\n";

            totalWT+=p[i].waitingTime;
            totalTAT+=p[i].turnAroundTime;
        }

        cout<<"\nAverage Waiting Time = "<<(float)totalWT/n;
        cout<<"\nAverage Turnaround Time = "<<(float)totalTAT/n<<endl;
    }
};

int main() {
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;
    Process *p=new Process[n];
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        cout<<"CPU Burst Time for Process "<<p[i].id<<": ";
        cin>>p[i].burstTime;
    }
    cout<<endl<<"Shortest Job First (SJF): "<<endl;
    SJF s(p,n);
    s.sortByBurstTime();  
    s.calculate();
    s.display();
    
    return 0;
}