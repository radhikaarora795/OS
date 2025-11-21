// FCFS CPU Scheduling Algorithm
#include <iostream>
#include <algorithm>
using namespace std;

class Process{
public:
    int id;
    int BT;
    int WT;
    int TAT;

    Process():id(0),BT(0),WT(0),TAT(0)
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
        p[0].WT=0;  // first process has waiting time 0
        for(int i=1;i<n;i++){
            p[i].WT=p[i-1].WT+p[i-1].BT;
        }
        for(int i=0;i<n;i++){
            p[i].TAT=p[i].BT+p[i].WT;
        }
    }

    void display(){
        int totalWT=0;
        int totalTAT=0;
        cout<<"Process\tBurstTime\tWaitingTime\tTurn Around Time"<<endl;
        for(int i=0;i<n;i++){
            cout<<"P"<<p[i].id<<"\t"<<p[i].BT<<"\t\t"<<p[i].WT<<"\t\t\t"<<p[i].TAT<<endl;

            totalWT+=p[i].WT;
            totalTAT+=p[i].TAT;
        }
        cout<<"Average waiting time: "<<(float)totalWT/n<<endl;
        cout<<"Average turn around time: "<<(float)totalTAT/n;
    }
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
       sort(p,p+n,[](Process a, Process b){
        return a.BT<b.BT;
       });
    }

    void calculate(){
        p[0].WT=0;
        for(int i=1;i<n;i++){
            p[i].WT=p[i-1].WT+p[i-1].BT;
        }
        for(int i=0;i<n;i++){
            p[i].TAT=p[i].BT+p[i].WT;
        }
    }

    void display(){
        int totalWT=0;
        int totalTAT=0;
        cout<<"Process\tBurstTime\tWaitingTime\tTurn Around Time"<<endl;
        for(int i=0;i<n;i++){
            cout<<"P"<<p[i].id<<"\t"<<p[i].BT<<"\t\t"<<p[i].WT<<"\t\t\t"<<p[i].TAT<<endl;

            totalWT+=p[i].WT;
            totalTAT+=p[i].TAT;
        }
        cout<<"Average waiting time: "<<(float)totalWT/n<<endl;
        cout<<"Average turn around time: "<<(float)totalTAT/n;
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
        cin>>p[i].BT;
    }

    SJF f(p,n);
    f.sortByBurstTime();
    f.calculate();
    f.display();
    
    return 0;
}
